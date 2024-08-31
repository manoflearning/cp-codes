#include <bits/stdc++.h>
using namespace std;

const int dy[] = { 1, 0, -1, 0 };
const int dx[] = { 0, 1, 0, -1 };

int n, m;
int a[55][55], dist[55][55];
vector<pair<int, int>> chkn;
int ans = 1e9;

void bfs() {
	memset(dist, -1, sizeof(dist));

	queue<pair<int, int>> qu;
	for (auto& [y, x] : chkn) {
		if (a[y][x] != 2) continue;
		qu.push({ y, x });
		dist[y][x] = 0;
	}

	int res = 0;

	while (!qu.empty()) {
		auto [y, x] = qu.front();
		qu.pop();

		if (a[y][x] == 1) res += dist[y][x];

		for (int d = 0; d < 4; d++) {
			int ny = y + dy[d], nx = x + dx[d];
			// cout << ny << ' ' << nx << '\n';
			if (ny < 1 || n < ny || nx < 1 || n < nx) continue;
			if (dist[ny][nx] != -1) continue;
			// cout << ny << ' ' << nx << '\n';
			qu.push({ ny, nx });
			dist[ny][nx] = dist[y][x] + 1;
		}
	}

	ans = min(ans, res);
}

void backtracking(int idx, int cnt) {
	if (cnt == m) { bfs(); return; }
	if (idx == chkn.size()) return;
	// if (idx == 10) return;
	// cout << idx << '\n';

	backtracking(idx + 1, cnt);
	a[chkn[idx].first][chkn[idx].second] = 0;
	backtracking(idx + 1, cnt - 1);
	a[chkn[idx].first][chkn[idx].second] = 2;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
			if (a[i][j] == 2) chkn.push_back({ i, j });
		}

	backtracking(0, chkn.size());

	cout << ans;
}