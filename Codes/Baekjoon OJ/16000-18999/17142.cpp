#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
#include <climits>
using namespace std;

const int MAX = 50;

int n, m;
int lab[MAX][MAX]; // �Է����� �־��� ��ĭ, ��, ���̷��� ����
vector<pair<int, int>> virus; // ���̷����� ������ ��ġ ����
vector<pair<int, int>> active; // Ȱ��ȭ�� ���̷����� ��ġ ����
bool visited[MAX][MAX]; // BFS �� ť�� �ߺ����� ��ǥ�� ���� ���� ����
int cnt; // �������Ѿ� �� ��ĭ�� ����

int ans = INT_MAX;

void backtrack(int flag); //Ȱ��ȭ�� ���̷��� ������
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
	int count = 0, TIME = 0; //ä�� ��ĭ�� ��, �� ���� �ð�
	//ť ����ü ����, ť���� Ȱ��ȭ�� ���̷��� ����
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
���� �ع�		: ��Ʈ��ŷ + bfs
���� ���		: 
������ ������		: ���� ��ġ�� �ʱ⿡ ��ĭ���� �־��� ��ġ�� ����, �� �����ð� ����
���� ����		: 1. ��Ȱ��ȭ�� ���̷����� �����ִ���, ������ ������. ���� ���� ���� �������� ���� ������ �Ұ�����.
				  2.
*/////////////////////////////////////////////////////////////////////