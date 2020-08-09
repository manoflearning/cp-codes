#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

struct bb {
	int y;
	int x;
	int t;
};

const int MV[4][2] = { {-1, 0},{0, -1}, {1,0},{0,1} };

int n;
int space[21][21];
int sy, sx, sw = 2, se = 0;
vector<bb> eat;
bool visited[21][21];

int bfs();
bool cmp(bb a, bb b);

int main() {
	cin >> n;

	for (int y = 1; y <= n; y++) {
		for (int x = 1; x <= n; x++) {
			cin >> space[y][x];

			if (space[y][x] == 9) {
				sy = y, sx = x;
				space[y][x] = 0;
			}
		}
	}

	int ans = 0;
	while (true) {
		bfs();
		
		if (eat.empty()) break;

		sort(eat.begin(), eat.end(), cmp);

		se++;
		if (se == sw) se = 0, sw++;

		ans += eat[0].t;
		space[eat[0].y][eat[0].x] = 0;
		sy = eat[0].y, sx = eat[0].x;

		eat.clear();
	}

	cout << ans;

	return 0;
}

int bfs() {
	memset(visited, 0, sizeof(visited));

	queue<bb> q;
	q.push({ sy, sx, 0 });
	visited[sy][sx] = true;

	while (!q.empty()) {
		int y = q.front().y, x = q.front().x, t = q.front().t;

		if (space[y][x] != 0 && space[y][x] < sw) {
			eat.push_back({ y, x, t });
		}

		for (int i = 0; i < 4; i++) {
			int Y = y + MV[i][0], X = x + MV[i][1];

			if (Y < 1 || n < Y || X < 1 || n < X) continue;
			if (visited[Y][X]) continue;
			if (space[Y][X] > sw) continue;

			visited[Y][X] = true;

			q.push({ Y, X, t + 1 });
		}

		q.pop();
	}

	return 0;
}

bool cmp(bb a, bb b) {
	if (a.t != b.t) return a.t < b.t;
	if (a.y != b.y) return a.y < b.y;
	return a.x < b.x;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: bfs, 구현
접근 방식		: 
결정적 깨달음		: 
오답 원인		: 1. 가장 가까운 먹을 수 있는 물고기가 여러 마리일 때, 우선 순위를 정하는 것을 bfs로 처리하지 못함. 따로 처리과정을 만들어야함.
				  2. 
*/////////////////////////////////////////////////////////////////////