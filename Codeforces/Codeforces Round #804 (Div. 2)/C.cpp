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

ll fac[101010];

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    fac[1] = 1;
    FOR(i, 2, 101010) fac[i] = i * fac[i - 1] % MOD;

	int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vt<ll> a(n), loc(n, -1);
        EACH(i, a) cin >> i;

        FOR(n) loc[a[i]] = i;

        if (loc[1] < loc[0]) {
            reverse(all(a));
            FOR(n) loc[a[i]] = i;
        }

        ll ans = 1;
        ll lb = loc[0], rb = loc[1];
        for (int i = 2; i < n; i++) {
            if (rb < loc[i] || loc[i] < lb) {
                lb = min(loc[i], lb);
                rb = max(loc[i], rb);
                continue;
            }
            else { 
                ans = ans * (rb - lb + 1 - i) % MOD;
            }
        }
        
        cout << ans << '\n';
    }

	return 0;
}