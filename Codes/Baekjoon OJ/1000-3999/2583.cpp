#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int m, n, k;
bool canGo[100][100];
bool visited[100][100];

int dfs(int y, int x);

int main() {
	//reset
	for (int i = 0; i < 100; i++)
		for (int l = 0; l < 100; l++)
			canGo[i][l] = true;

	cin >> m >> n >> k;
	//못가는 길 저장
	for (int i = 0; i < k; i++) {
		int s_x, s_y, e_x, e_y;
		cin >> s_x >> s_y >> e_x >> e_y;

		for (int y = s_y; y < e_y; y++)
			for (int x = s_x; x < e_x; x++)
				canGo[y][x] = false;
	}
	//dfs
	int ans1 = 0;
	vector<int> ans2;
	for (int y = 0; y < m; y++) {
		for (int x = 0; x < n; x++) {
			if (!visited[y][x] && canGo[y][x]) {
				ans1++;
				ans2.push_back(dfs(y, x));
			}
		}
	}

	sort(ans2.begin(), ans2.end());

	cout << ans1 << '\n';
	for (int i = 0; i < ans2.size(); i++)
		cout << ans2[i] << ' ';

	return 0;
}

int dfs(int y, int x) {
	visited[y][x] = true;

	int ret = 1;

	if (y > 0 && !visited[y - 1][x] && canGo[y - 1][x])
		ret += dfs(y - 1, x);
	if (y < m - 1 && !visited[y + 1][x] && canGo[y + 1][x])
		ret += dfs(y + 1, x);
	if (x > 0 && !visited[y][x - 1] && canGo[y][x - 1])
		ret += dfs(y, x - 1);
	if (x < n - 1 && !visited[y][x + 1] && canGo[y][x + 1])
		ret += dfs(y, x + 1);

	return ret;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: dfs
접근 방식		: dfs로 연결 요소의 개수와 각 연결 요소의 크기를 구할 수 있다.
결정적 깨달음		: 
오답 원인		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////