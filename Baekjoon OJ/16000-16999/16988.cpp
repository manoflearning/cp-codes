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

int n, m;
int a[22][22], vi[22][22];

pii dfs(int y, int x) {
    vi[y][x] = 1;
    pii ret = { 1, 1 };
    FOR(4) {
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;
        if (vi[ny][nx]) continue;

        if (a[ny][nx] == 0) ret.fr = 0;
        if (a[ny][nx] == 2) {
            pii res = dfs(ny, nx);
            ret.fr &= res.fr;
            ret.sc += res.sc;
        }
    }
    return ret;
}

int cal() {
    int ret = 0;
    memset(vi, 0, sizeof(vi));
    FOR(n) {
        FOR(j, m) {
            if (vi[i][j] || a[i][j] != 2) continue;
            pii res = dfs(i, j);
            if (res.fr) ret += res.sc;
        }
    }
    return ret;
}

int bt(int idx) {
    if (idx == 2) {
        return cal();
    }

    int ret = 0;
    FOR(n) {
        FOR(j, m) {
            if (a[i][j]) continue;
            a[i][j] = 1;
            ret = max(ret, bt(idx + 1));
            a[i][j] = 0;
        }
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

	cin >> n >> m;
    FOR(n) {
        FOR(j, m) {
            cin >> a[i][j];
        }
    }

    cout << bt(0);

	return 0;
}