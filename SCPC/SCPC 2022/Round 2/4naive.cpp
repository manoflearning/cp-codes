#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

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

int n, a[303][303];
int dpmn[303][303], dpmx[303][303];

int main() {
	#ifndef ONLINE_JUDGE
	// Enter the absolute path of the local file input.txt, output.txt
	// Or just enter the "input.txt", "output.txt"
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

    // 그룹 3은 최대 O(N^3) 정도를 허용.
    
	int tc; cin >> tc;
    FOR(tt, 1, tc + 1) {
        cout << "Case #" << tt << endl;

        cin >> n;
        FOR(n) FOR(j, n) {
            //cin >> a[i][j];
            a[i][j] = n * i + j + 1;
        }

        ll ans = 0;
        FOR(sy, n) {
            FOR(sx, n) {
                FOR(ey, sy, n) {
                    FOR(ex, sx, n) {
                        int mn = a[ey][ex], mx = a[ey][ex];

                        if (sy < ey) {
                            mn = min(mn, dpmn[ey - 1][ex]);
                            mx = max(mx, dpmx[ey - 1][ex]);
                        }
                        if (sx < ex) {
                            mn = min(mn, dpmn[ey][ex - 1]);
                            mx = max(mx, dpmx[ey][ex - 1]);
                        }

                        dpmn[ey][ex] = mn;
                        dpmx[ey][ex] = mx;

                        if ((mx - mn + 1) == (ey - sy + 1) * (ex - sx + 1)) ans++;
                    }
                }
            }
        }
        cout << ans << endl;
    }

	return 0;
}