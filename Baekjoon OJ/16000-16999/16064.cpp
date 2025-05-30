// solution 1: floyd-warshall
#define _USE_MATH_DEFINES
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
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n, m;
ll adj[1010][1010];

void init() {
    FOR(1010) FOR(j, 1010) adj[i][j] = INF;
    FOR(1010) adj[i][i] = 0;
}

void input() {
    cin >> n >> m;
    FOR(m) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u][v] = min<ll>(adj[u][v], -w);
    }
}

void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int u = 1; u <= n; u++) {
            if (adj[u][k] == INF) continue;
            for (int v = 1; v <= n; v++) {
                if (adj[k][v] == INF) continue;
                adj[u][v] = min(adj[u][v], adj[u][k] + adj[k][v]);
            }
        }
    }
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

    floyd();

    ll ans = INF;
    FOR(i, 1, n + 1) {
        FOR(j, 1, n + 1) {
            ans = min(ans, adj[i][j]);
            //cout << i << ' ' << j << ' ' << adj[i][j] << '\n';
        }
    }

    cout << -ans;

	return 0;
}

// solution 2: DAG dp
/*#define _USE_MATH_DEFINES
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
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

struct wv {
    ll w; int v;
};

int n, m;
vt<wv> adj[1010];
ll dp[1010];

void init() {
    FOR(1010) dp[i] = -1;
}

void input() {
    cin >> n >> m;
    FOR(m) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
    }
}

ll f(int v) {
    ll& ret = dp[v];
    if (ret != -1) return ret;
    if (adj[v].empty()) return ret = 0;

    ret = 0;
    EACH(i, adj[v]) {
        ret = max(ret, f(i.v) + i.w);
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

    ll ans = 0;
    FOR(i, 1, n + 1) 
        ans = max(ans, f(i));

    cout << ans;

	return 0;
}*/