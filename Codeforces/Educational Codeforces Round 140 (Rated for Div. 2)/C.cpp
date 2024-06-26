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
const int MOD = 998244353;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n, a[202][202];
ll dp[202][202][202];

void init() {
    FOR(202) FOR(j, 202) FOR(k, 202) dp[i][j][k] = -1;
}

ll f(int v, int last0, int last1) {
    ll& ret = dp[v][last0][last1];
    if (ret != -1) return ret;
    if (v == n + 1) return ret = 1;

    ret = 0;

    int pos0 = 1, pos1 = 1;
    for (int i = 1; i <= v; i++) {
        int vi0 = (i <= last0);
        int vi1 = (i <= last1);

        if (a[i][v] == 0) continue;
        if (a[i][v] == 1) {
            if (vi0 && vi1) return ret = 0;
            else if (vi0) pos1 = 0;
            else if (vi1) pos0 = 0;
        }
        if (a[i][v] == 2) {
            if (vi0 && vi1) continue;
            else if (vi0) pos0 = 0;
            else if (vi1) pos1 = 0;
            else return ret = 0;
        }
    }

    if (pos0) ret = (ret + f(v + 1, v, last1)) % MOD;
    if (pos1) ret = (ret + f(v + 1, last0, v)) % MOD;

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

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    cout << f(1, 0, 0);

	return 0;
}