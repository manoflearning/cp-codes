// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
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

const int MAXQ = 505050;

int flag;  // array size
struct Seg {  // 1-indexed
	vector<ll> t;
	void build(int n) {
        t.clear();
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
		// for (int i = flag; i < flag + n; i++) cin >> t[i];
		// for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void add(int p, ll value) {  // add value at position p
		for (t[p += flag - 1] += value; p > 1; p >>= 1) 
            t[p >> 1] = t[p] + t[p ^ 1];
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
	}
}seg;

int q;
vector<int> t[MAXQ];
struct State { ll w; int t; };
vector<State> arr[MAXQ];
int sz = 1;
ll ans[MAXQ];

void init() {
    for (int i = 1; i <= sz; i++) {
        t[i].clear();
        arr[i].clear();
        ans[i] = 0;
    }
    sz = 1;
}

void dfs(int v, int prv) {
    for (auto& it : arr[v]) seg.add(it.t, it.w);

    ans[v] = seg.query(v, sz);
    for (auto& i : t[v]) {
        if (i != prv) dfs(i, v);
    }

    for (auto& it : arr[v]) seg.add(it.t, -it.w);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cin >> q;
        for (int i = 0; i < q; i++) {
            int op, v, x;
            cin >> op >> v;

            if (op == 1) t[v].push_back(++sz);
            if (op == 2) {
                cin >> x;
                arr[v].push_back({ x, sz });
            }
        }

        seg.build(sz);
        dfs(1, -1);

        for (int v = 1; v <= sz; v++)
            cout << ans[v] << ' ';
        cout << '\n';

        init();
    }
}