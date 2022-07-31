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
        int n, m;
        cin >> n >> m;

        vt<vt<ll>> a(n, vt<ll>(m));
        FOR(i, n) {
            EACH(j, a[i]) cin >> j;
        }

        vt<vt<ll>> psum(n, vt<ll>(m));
        FOR(i, n) {
            psum[i][0] = a[i][0];
            FOR(j, 1, m) {
                psum[i][j] = a[i][j] + psum[i][j - 1];
            }
        }

        int idx = -1;
        FOR(j, m) {
            int bit = 1;
            FOR(i, n - 1) {
                if (psum[i][j] != psum[i + 1][j]) bit = 0;
            }

            if (bit) {
                idx = j + 1;
                break;
            }
        }

        int ans1 = -1;
        FOR(i, n) {
            FOR(j, idx, m - 1) {
                if (a[i][j] > a[i][j + 1]) ans1 = i;
            }
        }

        ll ans2 = 0;
        FOR(j, idx + 2, m) {
            ans2 += a[ans1][j] * (j - idx) / 2;
        }
        cout << idx << ' ' << '\n';
        cout << ans1 << ' ' << ans2 << '\n';
    }

	return 0;
}