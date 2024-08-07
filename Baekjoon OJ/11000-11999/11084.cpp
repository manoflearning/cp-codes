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
const int MOD = 1e9 + 9;
const int dy[] = { 2, 1, 2, -1, -2, 1, -2, -1 };
const int dx[] = { 1, 2, -1, 2, 1, -2, -1, -2 };

int r, c;
ll dp[404][404], dist[404][404];

void dfs() {
    FOR(404) FOR(j, 404) dist[i][j] = -1;

    queue<pii> q;
    q.push({ 1, 1 });
    dist[1][1] = 0;
    dp[1][1] = 1;

    while (sz(q)) {
        int y = q.front().fr, x = q.front().sc;
        q.pop();
        FOR(8) {
            int ny = y + dy[i], nx = x + dx[i];
            if (ny < 1 || r < ny | nx < 1 || c < nx) continue;
            if (dist[ny][nx] == -1 || dist[ny][nx] == dist[y][x] + 1) dp[ny][nx] = (dp[ny][nx] + dp[y][x]) % MOD;
            if (dist[ny][nx] == -1) {
                dist[ny][nx] = dist[y][x] + 1;
                q.push({ ny, nx });
            }
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

	cin >> r >> c;

    dfs();

    if (dist[r][c] == -1) cout << "None";
    else cout << dist[r][c] << ' ' << dp[r][c];

	return 0;
}