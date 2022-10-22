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

int n, m, vi[404][404];
vt<string> a;

void input() {
    cin >> n >> m;
    a.resize(n + 2);
    FOR(i, m + 2) {
        a[0].push_back('#');
        a[n + 1].push_back('#');
    }
    FOR(i, 1, n + 1) {
        string s; cin >> s;
        a[i].push_back('#');
        EACH(j, s) a[i].push_back(j);
        a[i].push_back('#');
    }

    n += 2, m += 2;
}

int cntr, cntc;

void dfs(int y, int x) {
    vi[y][x] = 1;

    FOR(4) {
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;
        if (vi[ny][nx]) continue;

        if (a[ny][nx] == '.') dfs(ny, nx);
        if (a[ny][nx] == '#') {
            if (i == 1) cntr++;
            if (i == 3) cntc++;
        }
    }
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

    int ans = 0;
    FOR(i, n) {
        FOR(j, m) {
            if (vi[i][j] || a[i][j] == '#') continue;
            cntr = 0, cntc = 0;
            dfs(i, j);
            cout << cntr << ' ' << cntc << '\n';
            ans += min(cntr, cntc);
        }
    }

    cout << ans;

	return 0;
}