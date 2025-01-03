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

ll n, mx, mxc;
vt<ll> a, psum, rpsum;

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	cin >> n >> mx >> mxc;

    a.resize(n);
    EACH(i, a) cin >> i;

    psum.resize(n);
    rpsum.resize(n);
    FOR(i, 1, n) psum[i] = a[i] - a[0] + psum[i - 1]; 
    FOR(i, n - 2, -1, -1) rpsum[i] = a[n - 1] - a[i] + rpsum[i + 1];

    ll ans = 0;

    FOR(i, 0, n) {
        ll l = i, r = n - 1;
        while (l < r) {
            ll mid = (l + r + 1) / 2;

            ll x = (i + mid) / 2;

            ll cost = 0;
            cost += psum[mid] - psum[x] - (mid - x) * (a[x] - a[0]);
            cost += rpsum[i] - rpsum[x] - (x - i) * (a[n - 1] - a[x]);

            if (cost <= mxc) l = mid;
            else r = mid - 1;
        }

        ans = max(ans, r - i + 1);
    }

    cout << ans;

	return 0;
}