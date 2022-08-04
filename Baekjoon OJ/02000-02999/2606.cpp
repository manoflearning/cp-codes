#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<int> com[101];
bool visited[101];
int ans = 0;

void bfs(int node);

int main() {
	int n, m;
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;

		com[x].push_back(y);
		com[y].push_back(x);
	}

	bfs(1);

	cout << ans;

	return 0;
}

void bfs(int node) {
	queue<int> q;

	q.push(node);
	visited[node] = true;
	
	while (!q.empty()) {
		for (int i = 0; i < com[q.front()].size(); i++) {
			if (visited[com[q.front()][i]]) continue;

			q.push(com[q.front()][i]);
			visited[com[q.front()][i]] = true;
			ans++;
		}

		q.pop();
	}
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: bfs
���� ���		: �ʺ� �켱 Ž�� ����� ���� �� ���� ����� ��� ����� ������ �� �� �ִ�.
������ ������		: 
���� ����		: 1.
				  2.
*/////////////////////////////////////////////////////////////////////