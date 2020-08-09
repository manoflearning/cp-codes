#include <iostream>
#include <algorithm>
using namespace std;

int r, c;
char b[21][21];
bool visited[26];

int dfs(int y, int x);

int main() {
	cin >> r >> c;

	for (int y = 1; y <= r; y++)
		for (int x = 1; x <= c; x++)
			cin >> b[y][x];
	
	cout << dfs(1, 1);

	return 0;
}

int dfs(int y, int x) {
	visited[b[y][x] - 'A'] = true;
	
	int ret = 0;

	if (y > 1 && !visited[b[y - 1][x] - 'A'])
		ret = max(ret, dfs(y - 1, x));
	if (y < r && !visited[b[y + 1][x] - 'A'])
		ret = max(ret, dfs(y + 1, x));
	if (x > 1 && !visited[b[y][x - 1] - 'A'])
		ret = max(ret, dfs(y, x - 1));
	if (x < c && !visited[b[y][x + 1] - 'A'])
		ret = max(ret, dfs(y, x + 1));
	
	visited[b[y][x] - 'A'] = false;

	return ret += 1;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: dfs의 응용
접근 방식		: visited 배열을 노드의 좌표 대신, 노드의 값으로 구현. 일반적인 dfs로는 최단거리 혹은 최장거리를 구할 수 없으므로 visited 배열을 dfs함수가 값을 반환하기 직전 false로 선언.
결정적 깨달음		: 
오답 원인		: 1. dp를 좌표값만을 기준으로 구현하는 것은 잘못됨. 최적 부분 구조가 아니기 때문.
				  2.
*/////////////////////////////////////////////////////////////////////