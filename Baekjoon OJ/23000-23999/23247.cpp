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

ll a[303][303], psum[303][303];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n, m;
    cin >> n >> m;

    FOR(i, 1, n + 1) 
        FOR(j, 1, m + 1) 
            cin >> a[i][j];

    psum[1][1] = a[1][1];
    FOR(i, 2, n + 1) 
        psum[i][1] = a[i][1] + psum[i - 1][1];
    FOR(i, 2, m + 1) 
        psum[1][i] = a[1][i] + psum[1][i - 1];

    FOR(i, 2, n + 1) {
        FOR(j, 2, m + 1) {
            psum[i][j] = a[i][j];
            psum[i][j] += psum[i][j - 1];
            psum[i][j] += psum[i - 1][j];
            psum[i][j] -= psum[i - 1][j - 1];
        }
    }

    ll ans = 0;
    for (int sy = 1; sy <= n; sy++) {
        for (int sx = 1; sx <= m; sx++) {
            for (int ey = sy; ey <= min(sy + 10, n); ey++) {
                for (int ex = sx; ex <= min(sx + 10, m); ex++) {
                    ll res = psum[ey][ex] - psum[ey][sx - 1] - psum[sy - 1][ex] + psum[sy - 1][sx - 1];

                    if (res == 10) ans++;
                }
            }
        }
    }

    cout << ans;

	return 0;
}