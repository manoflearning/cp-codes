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

ll gcd(ll a, ll b) {
	if (b == 0) return a;
	else return gcd(b, a % b);
}

// Bézout's identity
// Let a and b be integers with greatest common divisor d.
// Then there exist integers x and y such that ax + by = d. 
// Moreover, the integers of the form az + bt are exactly the multiples of d.

pair<pll, ll> egcd(ll a, ll b) { // time complexity: O(max(loga, logb))
    ll s = 0, olds = 1;
    ll t = 1, oldt = 0;
    ll r = b, oldr = a;

    while (r != 0) {
        ll q = oldr / r, tmp = -1;
        tmp = oldr - q * r;
        oldr = r, r = tmp;
        tmp = olds - q * s;
        olds = s, s = tmp;
        tmp = oldt - q * t;
        oldt = t, t = tmp;
    }

    // The integers x and y are called Bézout coefficients for (a, b)
    // Bézout coefficients: (olds, oldt)
    // greatest common divisor: oldr
    // quotients by the gcd: (t, s)
    return { { olds, oldt }, oldr };
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
		ll a, b, q;
        cin >> a >> b >> q;

        pair<pll, ll> ans = egcd(a, b);
        
        if (ans.sc < 0) {
            ans.fr.fr *= -1;
            ans.fr.sc *= -1;
            ans.sc *= -1;
        }
        if (ans.sc ^ q) {
            ans.fr.fr *= q / ans.sc, ans.fr.sc *= q / ans.sc;
        }

        ll l = -INF, r = INF;
        while (l < r) {
            ll mid = (l + r + 1) >> 1;
            ll resx = ans.fr.fr + mid * b / ans.sc;
            ll resy = ans.fr.sc - mid * a / ans.sc;
            //cout << mid << '\n';
            if (resx > 0 && resy > 0) l = mid;
            else r = mid - 1;
        }

        ans.fr.fr += l * b / ans.sc;
        ans.fr.sc -= l * a / ans.sc;

        cout << ans.fr.fr << ' ' << ans.fr.sc << '\n';
	}

	return 0;
}