#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
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
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

struct wv {
    int w, v, idx;
};

int n;
vt<wv> adj[50505];
ll dp[151515];

void init() {
    FOR(151515) dp[i] = -1;
}

void input() {
    cin >> n;
    FOR(n - 1) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v, 2 * i });
        adj[v].push_back({ w, u, 2 * i + 1 });
    }
}

ll f(int v, int prv, int idx) {
    ll& ret = dp[idx];
    if (ret != -1) return ret;
    if (sz(adj[v]) == 1 && prv > 0) return ret = 0; 

    EACH(i, adj[v]) {
        if (i.v == prv) continue;
        ret = max(ret, f(i.v, v, i.idx) + i.w);
    }

    return ret;
}

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	init();

    input();

    FOR(v, 1, n + 1) {
        cout << f(v, 0, 2 * (n - 1) + v) << '\n';
    }

	return 0;
}