#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int n;
int h[101][101];
bool visited[101][101];

void dfs(int y, int x, int rain);

int main() {
	cin >> n;

	for (int y = 1; y <= n; y++)
		for (int x = 1; x <= n; x++)
			cin >> h[y][x];
	
	int ans = 0;

	for (int rain = 0; rain < 100; rain++) {
		memset(visited, 0, sizeof(visited));

		int count = 0;

		for (int y = 1; y <= n; y++)
			for (int x = 1; x <= n; x++)
				if (!visited[y][x] && h[y][x] > rain) {
					count++;
					dfs(y, x, rain);
				}

		ans = max(ans, count);
	}

	cout << ans;

	return 0;
}

void dfs(int y, int x, int rain) {
	visited[y][x] = true;

	if (y > 1 && !visited[y - 1][x] && h[y - 1][x] > rain)
		dfs(y - 1, x, rain);
	if (y < n && !visited[y + 1][x] && h[y + 1][x] > rain)
		dfs(y + 1, x, rain);
	if (x > 1 && !visited[y][x - 1] && h[y][x - 1] > rain)
		dfs(y, x - 1, rain);
	if (x < n && !visited[y][x + 1] && h[y][x + 1] > rain)
		dfs(y, x + 1, rain);
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: dfs
접근 방식		: 시간복잡도 O(n^2). 높이가 100이하이므로, 빗물의 높이를 0이상 99이하까지 고려해야 함. 따라서 연산의 수는 약 최대 100^3. dfs로 연결요소의 개수를 알 수 있다.
결정적 깨달음		: 
오답 원인		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////