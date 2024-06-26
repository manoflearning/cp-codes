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

int n, k, SB[55];
vt<int> adj[55], t[55];
ll dp[55][55][55];

void init() {
    FOR(55) FOR(j, 55) FOR(k, 55) dp[i][j][k] = -1;
}

void input() {
    cin >> n >> k;
    FOR(n - 1) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void dfs(int v, int prv) {
    SB[v] = 1;
    EACH(i, adj[v]) {
        if (i == prv) continue;
        dfs(i, v);
        t[v].push_back(i);
        SB[v] += SB[i];
    }
}

int sb(int v, int idx) {
    int ret = SB[v];
    FOR(i, 0, idx) ret -= SB[t[v][i]];
    return ret;
}

ll f(int v, int idx, int sum) {
    ll& ret = dp[v][idx][sum];
    if (ret != -1) return ret;
    if (sum <= 1) return ret = 1;
    if (sb(v, idx) < sum) return ret = 0;

    ret = 0;
    int chd = t[v][idx];
    if (idx == sz(t[v]) - 1) ret = f(chd, 0, sum - 1);
    else {
        FOR(l, 0, sum) {
            int r = (sum - 1) - l;
            ret = (ret + f(chd, 0, l) * f(v, idx + 1, r + 1)) % MOD;
        }
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

    dfs(1, 0);

    ll ans = 0;
    FOR(i, 1, n + 1)
        ans = (ans + f(i, 0, k)) % MOD;

    /*cout << f(1, 0, 3) << '\n';
    cout << f(1, 1, 3) << '\n';
    cout << f(1, 2, 3) << '\n';
    cout << f(1, 3, 3) << '\n';*/

    cout << ans;

	return 0;
}