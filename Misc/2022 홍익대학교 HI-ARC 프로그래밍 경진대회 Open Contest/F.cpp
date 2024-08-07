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

int n, m, k, dist[3030][3030];
bool a[3030][3030];

bool check(int y, int x) {
    return (1 <= y && y <= n && 1 <= x && x <= m);
}

void bfs() {
    for (int i = 1; i <= n; i++) {
        memset(dist[i], -1, sizeof(dist[i]));
    }

    queue<pii> q;
    q.push({ 1, 1 });
    dist[1][1] = 0;

    while (sz(q)) {
        int y = q.front().fr, x = q.front().sc;
        q.pop();

        if (y == n && x == m) return;

        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i], nx = x + dx[i];
            if (!check(ny, nx)) continue;
            if (a[ny][nx]) continue;
            if (dist[ny][nx] != -1) continue;
            q.push({ ny, nx });
            dist[ny][nx] = dist[y][x] + 1;
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

	cin >> n >> m >> k;
    FOR(k) {
        int y, x, d;
        cin >> y >> x >> d;

        int ny = y - d, nx1 = x, nx2 = x;
        while (ny != y) {
            if (check(ny, nx1)) a[ny][nx1] = 1;
            if (check(ny, nx2)) a[ny][nx2] = 1;
            ny++, nx1--, nx2++;
        }
        if (check(ny, nx1)) a[ny][nx1] = 1;
        if (check(ny, nx2)) a[ny][nx2] = 1;

        ny = y + d, nx1 = x, nx2 = x;
        while (ny != y) {
            if (check(ny, nx1)) a[ny][nx1] = 1;
            if (check(ny, nx2)) a[ny][nx2] = 1;
            ny--, nx1--, nx2++;
        }
        if (check(ny, nx1)) a[ny][nx1] = 1;
        if (check(ny, nx2)) a[ny][nx2] = 1;
    }

    bfs();

    if (dist[n][m] >= 0) {
        cout << "YES\n" << dist[n][m];
    }
    else cout << "NO";

	return 0;
}