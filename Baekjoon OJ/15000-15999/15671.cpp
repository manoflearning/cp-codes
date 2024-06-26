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

int n, a[10][10];

void init() {
    FOR(10) {
        FOR(j, 10) {
            a[i][j] = 2;
        }
    }
}

int meet(int y, int x, int idx, int bit) {
    while (1 <= y && y <= 6 && 1 <= x && x <= 6) {
        if (a[y][x] == 2) return 0;
        if (a[y][x] == bit) return 1;
        y += dy[idx], x += dx[idx];
    }
    return 0;
}

int isValid(int y, int x, int bit) {
    FOR(8) {
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 1 || 6 < ny || nx < 1 || 6 < nx) continue;
        if (a[ny][nx] != !bit) continue;

        ny += dy[i], nx += dx[i];
        if (ny < 1 || 6 < ny || nx < 1 || 6 < nx) continue;
        if (meet(ny, nx, i, bit)) return 1;
    }
    return 0;
}

void flip2(int y, int x, int idx, int bit) {
    while (1 <= y && y <= n && 1 <= x && x <= n) {
        if (a[y][x] == !bit) a[y][x] = bit;
        else break;
        y += dy[idx], x += dx[idx];
    }
}

int flip(int y, int x, int bit) {
    a[y][x] = bit;
    FOR(8) {
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 1 || 6 < ny || nx < 1 || 6 < nx) continue;
        if (a[ny][nx] != !bit) continue;

        ny += dy[i], nx += dx[i];
        if (ny < 1 || 6 < ny || nx < 1 || 6 < nx) continue;
        if (meet(ny, nx, i, bit)) flip2(y + dy[i], x + dx[i], i, bit);
    }
    return 0;
}

void print() {
    int cnt0 = 0, cnt1 = 0;
    FOR(i, 1, 7) {
        FOR(j, 1, 7) {
            if (a[i][j] == 0) cnt0++;
            if (a[i][j] == 1) cnt1++;

            if (a[i][j] == 0) cout << 'B';
            if (a[i][j] == 1) cout << 'W';
            if (a[i][j] == 2) cout << '.';
        }
        cout << '\n';
    }
    if (cnt0 > cnt1) cout << "Black";
    else cout << "White";
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

	cin >> n;

    a[3][4] = a[4][3] = 0;
    a[3][3] = a[4][4] = 1;

    int bit = 0;
    FOR(n) {
        int y, x;
        cin >> y >> x;

        if (!isValid(y, x, bit)) bit = !bit;

        flip(y, x, bit);

        bit = !bit;
    }

    print();

	return 0;
}