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
int mnv[707][707];
vt<string> a;
int ey, ex;

void bfsv(int vsy, int vsx) {
	vt<vt<int>> dist(707, vt<int>(707, -1));

	queue<pii> q;
	q.push({ vsy, vsx });
	dist[vsy][vsx] = 0;

	while (sz(q)) {
		int y = q.front().fr, x = q.front().sc;
		q.pop();

		FOR(4) {
			int ny = y + dy[i], nx = x + dx[i];
			if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;
			if (a[ny][nx] == 'I') continue;
			if (dist[ny][nx] != -1) continue;

			q.push({ ny, nx });
			dist[ny][nx] = dist[y][x] + 1;
		}
	}

	FOR(y, n) {
		int prv = 0, mn = INF;
		FOR(x, m) {
			if (a[y][x] == 'I') {
				FOR(i, prv, x) mnv[y][i] = min(mnv[y][i], mn);
				prv = x + 1, mn = INF;
			}
			else {
				mn = min(mn, dist[y][x]);
			}
		}

		if (prv < m) {
			FOR(i, prv, m) mnv[y][i] = min(mnv[y][i], mn);
		}
	}

	FOR(x, m) {
		int prv = 0, mn = INF;
		FOR(y, n) {
			if (a[y][x] == 'I') {
				FOR(i, prv, y) mnv[i][x] = min(mnv[i][x], mn);
				prv = y + 1, mn = INF;
			}
			else {
				mn = min(mn, dist[y][x]);
			}
		}

		if (prv < n) {
			FOR(i, prv, n) mnv[i][x] = min(mnv[i][x], mn);
		}
	}
}

int bfsy(int sy, int sx) {
	vt<vt<int>> dist(707, vt<int>(707, -1));

	queue<pii> q;
	q.push({ sy, sx });
	dist[sy][sx] = 0;

	while (sz(q)) {
		int y = q.front().fr, x = q.front().sc;
		q.pop();

		if (dist[y][x] >= mnv[y][x] && !(y == 0 && x == 0)) continue;
		if (y == ey && x == ex) return 1;

		FOR(4) {
			int ny = y + dy[i], nx = x + dx[i];
			if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;
			if (a[ny][nx] == 'I') continue;
			if (dist[ny][nx] != -1) continue;

			q.push({ ny, nx });
			dist[ny][nx] = dist[y][x] + 1;
		}
	}

	return 0;
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

	FOR(707) FOR(j, 707) mnv[i][j] = INF;

	cin >> n >> m;
	a.resize(n);
	EACH(i, a) cin >> i;

	int vsy, vsx, sy, sx;
	FOR(i, n) FOR(j, m) {
		if (a[i][j] == 'V') vsy = i, vsx = j;
		if (a[i][j] == 'Y') sy = i, sx = j;
		if (a[i][j] == 'T') ey = i, ex = j;
	}

	bfsv(vsy, vsx);

	if (bfsy(sy, sx)) cout << "YES";
	else cout << "NO";

	return 0;
}