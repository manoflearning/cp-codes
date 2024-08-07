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
ll a[101010], dp[101010];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> m;
    FOR(n) cin >> a[i + 1];

    ll ans = 0;

    dp[1] = 1;
    ans += dp[1];
    
    FOR(i, 2, n + 1) {
        if (a[i] == a[i - 1]) dp[i] = dp[i - 1] + 1;
        else dp[i] = dp[i - 1] + (i - 1) + 1;
        ans += dp[i];
    }

    while (m--) {
        ll i, x;
        cin >> i >> x;

        if (i > 1) {
            if (a[i] == a[i - 1] && x != a[i - 1]) {
                ans += (i - 1) * (n - i + 1);
            }
            else if (a[i] != a[i - 1] && x == a[i - 1]) {
                ans -= (i - 1) * (n - i + 1);
            }
        }
        if (i < n) {
            if (a[i] == a[i + 1] && x != a[i + 1]) {
                ans += i * (n - i);
            }
            else if (a[i] != a[i + 1] && x == a[i + 1]) {
                ans -= i * (n - i);
            }
        }

        cout << ans << '\n';

        a[i] = x;
    }

	return 0;
}