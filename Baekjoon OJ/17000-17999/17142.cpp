#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
#include <climits>
using namespace std;

const int MAX = 50;

int n, m;
int lab[MAX][MAX]; // 입력으로 주어진 빈칸, 벽, 바이러스 정보
vector<pair<int, int>> virus; // 바이러스의 개수와 위치 정보
vector<pair<int, int>> active; // 활성화된 바이러스의 위치 정보
bool visited[MAX][MAX]; // BFS 시 큐에 중복으로 좌표가 들어가는 것을 방지
int cnt; // 감염시켜야 할 빈칸의 개수

int ans = INT_MAX;

void backtrack(int flag); //활성화할 바이러스 고르기
void BFS();

int main() {
	cin >> n >> m;

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			cin >> lab[y][x];

			if (lab[y][x] == 2) virus.push_back({ y, x });
			else if (lab[y][x] == 0) cnt++;
		}
	}
	//
	backtrack(-1);

	if (ans == INT_MAX) cout << -1;
	else cout << ans;

	return 0;
}

void backtrack(int flag) {
	//base case
	if (active.size() == m) {
		memset(visited, 0, sizeof(visited));
		BFS();
		return;
	}

	for (int i = flag + 1; i < virus.size(); i++) {
		active.push_back(virus[i]);
		backtrack(i);
		active.pop_back();
	}
}
void BFS() {
	int count = 0, TIME = 0; //채운 빈칸의 수, 총 감염 시간
	//큐 구조체 구현, 큐에다 활성화된 바이러스 삽입
	struct bb {
		int y;
		int x;
		int time;
	};
	queue<bb> q;
	for (int i = 0; i < active.size(); i++)
		q.push({ active[i].first, active[i].second, 0 });
	//bfs
	while (!q.empty()) {
		int y = q.front().y, x = q.front().x, t = q.front().time;

		if (y > 0 && !visited[y - 1][x] && lab[y - 1][x] != 1) {
			visited[y - 1][x] = true;
			if (lab[y - 1][x] == 0) count++;
			q.push({ y - 1, x, t + 1 });
		}
		if (y < n - 1 && !visited[y + 1][x] && lab[y + 1][x] != 1) {
			visited[y + 1][x] = true;
			if (lab[y + 1][x] == 0) count++;
			q.push({ y + 1, x, t + 1 });
		}
		if (x > 0 && !visited[y][x - 1] && lab[y][x - 1] != 1) {
			visited[y][x - 1] = true;
			if (lab[y][x - 1] == 0) count++;
			q.push({ y, x - 1, t + 1 });
		}
		if (x < n - 1 && !visited[y][x + 1] && lab[y][x + 1] != 1) {
			visited[y][x + 1] = true;
			if (lab[y][x + 1] == 0) count++;
			q.push({ y, x + 1, t + 1 });
		}

		if (lab[y][x] == 0) TIME = max(TIME, t);

		q.pop();
	}

	if (count == cnt) ans = min(ans, TIME);
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 백트래킹 + bfs
접근 방식		: 
결정적 깨달음		: 현재 위치가 초기에 빈칸으로 주어진 위치일 때만, 총 감염시간 갱신
오답 원인		: 1. 비활성화된 바이러스로 막혀있더라도, 감염은 가능함. 오직 벽에 의해 막혀있을 때만 감염이 불가능함.
				  2.
*/////////////////////////////////////////////////////////////////////