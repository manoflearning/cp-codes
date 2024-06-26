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

const int MAXN = 202020;

int flag;  // array size
struct Seg {  // 1-indexed
	vector<ll> t;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
		// for (int i = flag; i < flag + n; i++) cin >> t[i];
		// for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void add(int p) {  // add 1 at position p
		for (t[p += flag - 1]++; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
	}
}seg;

int n;
vector<int> t[MAXN], chd[MAXN];
int par[MAXN], in[MAXN], out[MAXN], ocnt;
ll ans[MAXN];

void input() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        t[u].push_back(v);
        t[v].push_back(u);
    }
}

void dfs(int v, int prv) {
    in[v] = ++ocnt;
    par[v] = prv;
    for (auto& i : t[v]) {
        if (i == prv) continue;
        chd[v].push_back(i);
        dfs(i, v);
    }
    out[v] = ocnt;
}

void solve() {
    seg.build(n);
    for (int w = 1; w <= n; w++) {
        // child
        for (auto& i : chd[w]) {
            ll cnt = seg.query(in[i], out[i]);
            ans[1] += cnt;
            ans[in[i]] -= cnt;
            ans[out[i] + 1] += cnt;
        }
        // parent
        ll cnt = seg.query(1, in[w] - 1) + seg.query(out[w] + 1, n);
        ans[in[w]] += cnt;
        ans[out[w] + 1] -= cnt;

        seg.add(in[w]);
    }

    for (int i = 1; i <= ocnt; i++) {
        ans[i] += ans[i - 1];
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    dfs(1, -1);

    solve();

    for (int i = 1; i <= ocnt; i++) {
        cout << ans[in[i]] << ' ';
    }
}