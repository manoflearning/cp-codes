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
const int dy[] = { -1, 0, 1, 0 };
const int dx[] = { 0, 1, 0, -1 };

int n, m, vi[10][10];
ll a[10][10];
vt<pii> dir = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 }};

ll bt(int y, int x) {
    if (y == n) return 0;

    if (vi[y][x]) {
        int ny = y, nx = x + 1;
        if (nx == m) nx = 0, ny++;
        return bt(ny, nx);
    }
    else {
        int ny = y, nx = x + 1;
        if (nx == m) nx = 0, ny++;
        ll ret = bt(ny, nx);

        vi[y][x] = 1;
        EACH(i, dir) {
            int y1 = y + dy[i.fr], x1 = x + dx[i.fr];
            int y2 = y + dy[i.sc], x2 = x + dx[i.sc];

            if (y1 < 0 || n <= y1 || x1 < 0 || m <= x1) continue;
            if (vi[y1][x1]) continue;
            if (y2 < 0 || n <= y2 || x2 < 0 || m <= x2) continue;
            if (vi[y2][x2]) continue;

            ll res = 2 * a[y][x] + a[y1][x1] + a[y2][x2];
            vi[y1][x1] = vi[y2][x2] = 1;
            ret = max(ret, res + bt(ny, nx));
            vi[y1][x1] = vi[y2][x2] = 0;
        }
        vi[y][x] = 0;

        return ret;
    }
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
    
	cin >> n >> m;
    FOR(n) FOR(j, m) cin >> a[i][j];

    cout << bt(0, 0);

	return 0;
}