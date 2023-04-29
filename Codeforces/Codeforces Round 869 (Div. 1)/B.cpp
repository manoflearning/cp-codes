#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int n, m;
vector<int> adj[2020];
vector<int> vi, path;

void init() {
    for (int i = 1; i <= n; i++) adj[i].clear();
    vi.clear(); path.clear();
}

void input() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

vector<int> stk;
void dfs(int v, int prv, int st) {
    vi[v] = 1;
    stk.push_back(v);
    for (auto& i : adj[v]) {
        if (i == prv) continue;
        if (i == st && path.empty()) path = stk;
    }
    for (auto& i : adj[v]) {
        if (i == prv) continue;
        if (!vi[i]) dfs(i, v, st);
    }
    stk.pop_back();
}

void makeAnswer() {
    cout << sz(path) + 2 << '\n';
    for (int i = 0; i < sz(path); i++) {
        int u = path[i], v = path[(i + 1) % sz(path)];
        cout << u << ' ' << v << '\n';
    }

    vector<int> banned(n + 1);
    for (auto& i : path) banned[i] = 1;

    int st = path[0], cnt = 0;
    for (auto& i : adj[st]) {
        if (banned[i]) continue;
        cout << st << ' ' << i << '\n';
        if (++cnt == 2) break;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        input();

        for (int v = 1; v <= n; v++) {
            if (sz(adj[v]) >= 4) {
                vi.clear();
                vi.resize(n + 1);
                dfs(v, -1, v);
            }
        }

        if (path.empty()) cout << "NO\n";
        else {
            cout << "YES\n";
            makeAnswer();
        }

        init();
    }
}
/*#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n, m;
vector<int> adj[2020];
int vi[2020], num[2020], top = 1;
int he = -1;

void input() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

int flag;  // array size
struct Seg {  // 1-indexed
	vector<pll> t;
	void build(int n) {
        t.clear();
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
		//for (int i = flag; i < flag + n; i++) cin >> t[i];
		//for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int p, pll value) {  // set value at position p
		for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]);
	}
    void add(int p, ll value) {  // set value at position p
		for (t[p += flag - 1].fr += value; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]);
	}
	pll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return { 0, 0 };
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}seg;

int now[2020];
vector<int> stk(1, 0);
vector<int> arr;

void dfs(int v, int prv) {
    vi[v] = 1;

    now[v] = 1;
    num[v] = top++;
    stk.push_back(v);
    
    seg.modify(num[v], { sz(adj[v]), v });
    for (auto& i : adj[v]) {
        if (now[i]) {
            seg.add(num[i], -1);
            seg.add(num[v], -1);
        }
    }
    
    for (auto& i : adj[v]) {
        if (i == prv) continue;

        if (vi[i]) {
            if (sz(arr)) continue;
            pll res = seg.query(num[i], num[v]);
            if (res.fr >= 2) {
                for (int j = num[i]; j <= num[v]; j++)
                    arr.push_back(stk[j]);
                he = res.sc;
            }
        }
    }

    for (auto& i : adj[v]) {
        if (i == prv) continue;
        if (!vi[i]) dfs(i, v);
    }

    now[v] = 0;
    --top;
    stk.pop_back();
}

vector<pii> ans;
void findSubGraph() {
    vector<int> banned;
    for (int i = 0; i < sz(arr); i++) {
        int u = arr[i], v = arr[(i + 1) % sz(arr)];
        ans.push_back({ u, v });
        if (u == he) banned.push_back(v);
        if (v == he) banned.push_back(u);
    }

    int cnt = 0;
    for (auto& i : adj[he]) {
        if (banned[0] == i || banned[1] == i) continue;
        ans.push_back({ he, i });
        if (++cnt == 2) break;
    }
}

void init() {
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
        vi[i] = num[i] = 0;
    }
    top = 1;
    he = -1;
    ans.clear();
    stk.clear();
    stk.push_back(0);
    arr.clear();
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
	for (int tt = 1; tt <= tc; tt++) {
		input();

        seg.build(n);

        for (int v = 1; v <= n; v++)
            if (!vi[v]) dfs(v, -1);

        if (arr.empty()) cout << "NO\n";
        else {
            findSubGraph();
            cout << "YES\n";
            cout << sz(ans) << '\n';
            for (auto& i : ans)
                cout << i.fr << ' ' << i.sc << '\n';
        }

        init();
	}

	return 0;
}*/