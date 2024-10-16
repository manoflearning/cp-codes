#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
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

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n, m, k;
int a[101][101], visited[101][101], ans;
vt<int> ans2;

void input() {
	cin >> m >> n >> k;
	FOR(k) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;

		FOR(y, y1, y2) {
			FOR(x, x1, x2) {
				a[y][x] = 1;
			}
		}
	}
}

int dfs(int y, int x) {
	int ret = 1;
	visited[y][x] = 1;

	FOR(4) {
		int ny = y + dy[i], nx = x + dx[i];
		if (ny < 0 || m <= ny || nx < 0 || n <= nx) continue;
		if (a[ny][nx] || visited[ny][nx]) continue;
		ret += dfs(ny, nx);
	}

	return ret;
}

void solve() {
	FOR(y, 0, m) {
		FOR(x, 0, n) {
			if (!a[y][x] && !visited[y][x]) {
				ans++;
				ans2.push_back(dfs(y, x));
			}
		}
	}
}

void output() {
	cout << ans << '\n';

	sort(all(ans2));
	EACH(i, ans2) cout << i << ' ';
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

	input();

	solve();

	output();

	return 0;
}