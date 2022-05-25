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

int n, m, d0[505][505], d1[505][505], d2[505][505], d3[505][505], d[505][505];
vt<vt<char>> a;
int sy, sx, ey, ex;
int vi[505][505];

void init() {
    FOR(505) {
        FOR(j, 505) {
            d0[i][j] = d1[i][j] = d2[i][j] = d3[i][j] = INF;
        }
    }
}

void input() {
    cin >> n >> m;
    a.resize(n + 2, vt<char>(m + 2));
    FOR(i, 1, n + 1) {
        FOR(j, 1, m + 1) {
            cin >> a[i][j];
            if (a[i][j] == 'V') sy = i, sx = j;
            if (a[i][j] == 'J') ey = i, ex = j;
        }
    }
}

void buildD() {
    FOR(i, 1, n + 1) {
        FOR(j, 1, m + 1) {
            d0[i][j] = min(d0[i - 1][j], d0[i][j - 1]) + 1;
            if (a[i][j] == '+') d0[i][j] = 0;
        }
    }

    FOR(i, n, 0, -1) {
        FOR(j, m, 0, -1) {
            d1[i][j] = min(d1[i + 1][j], d1[i][j + 1]) + 1;
            if (a[i][j] == '+') d1[i][j] = 0;
        }
    }

    FOR(i, 1, n + 1) {
        FOR(j, m, 0, -1) {
            d2[i][j] = min(d2[i - 1][j], d2[i][j + 1]) + 1;
            if (a[i][j] == '+') d2[i][j] = 0;
        }
    }

    FOR(i, n, 0, -1) {
        FOR(j, 1, m + 1) {
            d3[i][j] = min(d3[i + 1][j], d3[i][j - 1]) + 1;
            if (a[i][j] == '+') d3[i][j] = 0;
        }
    }

    FOR(i, 1, n + 1) {
        FOR(j, 1, m + 1) {
            d[i][j] = min({ d0[i][j], d1[i][j], d2[i][j], d3[i][j] });
        }
    }
}

int dfs(int y, int x, int l) {
    vi[y][x] = 1;
    if (y == ey && x == ex) return 1;

    int ret = 0;
    FOR(4) {
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 1 || n < ny || nx < 1 || m < nx) continue;
        if (vi[ny][nx]) continue;
        if (d[ny][nx] < l) continue;
        ret |= dfs(ny, nx, l);
    }
    return ret;
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

	input();

    buildD();

    FOR(i, d[sy][sx], -1, -1) {
        memset(vi, 0, sizeof(vi));
        if (dfs(sy, sx, i)) {
            cout << i;
            break;
        }
    }

	return 0;
}