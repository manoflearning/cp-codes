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

int n;
ll a[3][202020];
ll dp[3][202020];
ll p1l[202020], p1r[202020], p2l[202020], p2r[202020];

void init() {
    FOR(i, 1, n + 1) {
        a[1][i] = a[2][i] = dp[1][i] = dp[2][i] = 0;
        p1l[i] = p1r[i] = p2l[i] = p2r[i] = 0;
    }
    n = 0;
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
    FOR(tt, 1, tc + 1) {
        cin >> n;
        FOR(i, 1, 3) FOR(j, 1, n + 1) {
            cin >> a[i][j];
            a[i][j]++;
        }
        a[1][1] = 0;

        dp[1][1] = 0;
        dp[2][1] = max(1ll, a[2][1]);

        FOR(i, 2, n + 1) {
            if (i & 1) {
                dp[1][i] = max(a[1][i], dp[1][i - 1] + 1);
                dp[2][i] = max(a[2][i], dp[1][i] + 1);
            }
            else {
                dp[2][i] = max(a[2][i], dp[2][i - 1] + 1);
                dp[1][i] = max(a[1][i], dp[2][i] + 1);
            }
        }

        FOR(i, n, 0, -1) {
            p1l[i] = max(a[1][i] + (n - i), p1l[i + 1]);
            p1r[i] = max(a[1][i] + (i - 1), p1r[i + 1]);
            p2l[i] = max(a[2][i] + (n - i), p2l[i + 1]);
            p2r[i] = max(a[2][i] + (i - 1), p2r[i + 1]);
        }
        
        ll ans = (n & 1 ? dp[2][n] : dp[1][n]);
        FOR(i, 1, n + 1) {
            if (i & 1) {
                ll res = p1l[i] + (n - i + 1);
                res = max(res, p2r[i] - i + 1);
                ans = min(ans, max(dp[1][i] + 2 * (n - i + 1) - 1, res));
            }
            else {
                ll res = p2l[i] + (n - i + 1);
                res = max(res, p1r[i] - i + 1);
                ans = min(ans, max(dp[2][i] + 2 * (n - i + 1) - 1, res));
            }
        }

        cout << ans << '\n';

        init();
    }

	return 0;
}