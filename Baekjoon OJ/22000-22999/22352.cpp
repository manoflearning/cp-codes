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
vt<vt<int>> a, b, c;
int vi[33][33], cnt;
vt<pii> com[909];

void input() {
    cin >> n >> m;
    a.resize(n, vt<int>(m));
    b.resize(n, vt<int>(m));

    EACH(i, a) {
        EACH(j, i) cin >> j;
    }
    EACH(i, b) {
        EACH(j, i) cin >> j;
    }
}

void dfs(int y, int x) {
    vi[y][x] = cnt;
    com[cnt].push_back({ y, x });
    FOR(4) {
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;
        if (a[y][x] != a[ny][nx]) continue;
        if (vi[ny][nx]) continue;
        dfs(ny, nx);
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

    FOR(n) FOR(j, m) {
        if (!vi[i][j]) {
            cnt++;
            dfs(i, j);
        }
    }

    c = a;
    FOR(n) FOR(j, m) {
        if (a[i][j] ^ b[i][j]) {
            EACH(k, com[vi[i][j]]) {
                c[k.fr][k.sc] = b[i][j];
            }
            i = n, j = m;
            break;
        }
    }

    if (c == b) cout << "YES";
    else cout << "NO";

	return 0;
}