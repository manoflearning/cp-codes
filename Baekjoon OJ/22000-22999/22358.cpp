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
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

#define EXPAND( x ) x // Use this if MS Visual Studio doesn't expand __VA_ARGS__ correctly
#define F_OR(i, a, b, s) for (int i = (a); (s) > 0 ? i < (b) : i > (b); i += (s))
#define F_OR1(e) F_OR(i, 0, e, 1)
#define F_OR2(i, e) F_OR(i, 0, e, 1)
#define F_OR3(i, b, e) F_OR(i, b, e, 1)
#define F_OR4(i, b, e, s) F_OR(i, b, e, s)
#define GET5(a, b, c, d, e, ...) e
#define F_ORC(...) EXPAND( GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1) )
#define FOR(...) EXPAND( F_ORC(__VA_ARGS__ )(__VA_ARGS__) )
#define EACH(x, a) for (auto& x : a)

const double EPS = 1e-9;
const ll INF = 1e18 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

struct wv {
    ll w; int v;
};

int n, m, k, st, en;
vt<wv> adj[101010];
vt<int> radj[101010];
ll dp[101010][11];

void init() {
    FOR(101010) FOR(j, 11) dp[i][j] = -INF - 1;
}

void input() {
    cin >> n >> m >> k >> st >> en;
    FOR(m) {
        int u, v; ll w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        radj[v].push_back(u);
    }
}

ll f(int v, int cnt) {
    ll& ret = dp[v][cnt];
    if (ret != -INF - 1) return ret;
    if (v == en && cnt == 0) return ret = 0;

    if (v == en) ret = 0;
    else ret = -INF;

    EACH(i, adj[v]) {
        ret = max(ret, f(i.v, cnt) + i.w);
    }

    if (!cnt) return ret;

    EACH(i, radj[v]) {
        ret = max(ret, f(i, cnt - 1));
    }

    return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    init();

	input();

    ll ans = f(st, k);
    if (ans < 0) ans = -1;
    cout << ans;

	return 0;
}