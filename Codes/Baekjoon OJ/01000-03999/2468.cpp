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
���� �ع�		: dfs
���� ���		: �ð����⵵ O(n^2). ���̰� 100�����̹Ƿ�, ������ ���̸� 0�̻� 99���ϱ��� �����ؾ� ��. ���� ������ ���� �� �ִ� 100^3. dfs�� �������� ������ �� �� �ִ�.
������ ������		: 
���� ����		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////