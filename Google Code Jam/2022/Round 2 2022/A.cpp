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
const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };
const int dx[] = { 1, 0, -1, 0, 1, -1, 1, -1 };

int n, k;
vt<vt<int>> a;
int dp[44][44][39 * 39];

void draw() {
    int now = 1;
    
    int y = 0, x = 1, d = 0;
    a[0][0] = now;

    while (now < n * n) {
        a[y][x] = ++now;
        
        if (now == n * n) break;

        int cnt = 0;
        while (1) {
            int ny = y + dy[d], nx = x + dx[d];
            if (ny < 0 || n <= ny || nx < 0 || n <= nx || a[ny][nx] != 0) {
                d = (d + 1) % 4;
                continue;
            }
            y = ny, x = nx;
            break;
        }
    }
}

void init() {
    FOR(44) {
        FOR(j, 44) {
            FOR(k, 39 * 39) {
                dp[i][j][k] = -1;
            }
        }
    }
    a.clear();
}

int f(int y, int x, int cnt) {
    int& ret = dp[y][x][cnt];
    if (ret != -1) return ret;
    if (a[y][x] == n * n) {
        return ret = (cnt == k ? 0 : INF);
    }

    ret = INF;

    FOR(4) {
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 0 || n <= ny || nx < 0 || n <= nx) continue;
        if (a[ny][nx] < a[y][x]) continue;
        ret = min(ret, f(ny, nx, cnt + 1) + (a[ny][nx] - a[y][x] == 1 ? 0 : 1));
    }

    return ret;
}

void rf(int y, int x, int cnt) {
    if (a[y][x] == n * n) return;

    FOR(4) {
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 0 || n <= ny || nx < 0 || n <= nx) continue;
        if (a[ny][nx] < a[y][x]) continue;

        if (dp[y][x][cnt] == f(ny, nx, cnt + 1) + (a[ny][nx] - a[y][x] == 1 ? 0 : 1)) {
            if (a[ny][nx] - a[y][x] > 1) cout << a[y][x] << ' ' << a[ny][nx] << '\n';
            rf(ny, nx, cnt + 1);
            return;
        }
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
	
    init();

	int tc; cin >> tc;

    FOR(t, tc) {
        cout << "Case #" << t + 1 << ": ";

        cin >> n >> k;

        a.resize(n, vt<int>(n));
        
        draw();

        int res = f(0, 0, 0);
        if (res >= INF) cout << "IMPOSSIBLE\n";
        else {
            cout << res << '\n';
            rf(0, 0, 0);
        }

        init();
    }

	return 0;
}