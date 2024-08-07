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
vt<pii> adj[1010];
vt<int> t[1010];
int dp[1010], w[1010];

void init() {
    n = m = 0;
    FOR(1010) {
        adj[i].clear();
        t[i].clear();
    }
    memset(dp, -1, sizeof(dp));
    memset(w, 0, sizeof(w));
}

void input() {
    cin >> n >> m;
    FOR(m) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ v, w });
        adj[v].push_back({ u, w });
    }
}

void dfs(int v, int prv) {
    EACH(i, adj[v]) {
        if (i.fr == prv) continue;
        w[i.fr] = i.sc;
        t[v].push_back(i.fr);
        dfs(i.fr, v);
    }
}

int f(int v) {
    int& ret = dp[v];
    if (ret != -1) return ret;
    if (t[v].empty()) return ret = w[v];

    ret = w[v];
    int sum = 0;
    EACH(i, t[v]) sum += f(i);
    
    return ret = min(ret, sum);
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

	int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        if (n == 1) {
            cout << 0 << '\n';
            continue;
        }

        w[1] = INF;
        dfs(1, 0);

        cout << f(1) << '\n';
    }

	return 0;
}