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
문제 해법		: bfs
접근 방식		: 너비 우선 탐색 방식을 통해 한 노드와 연결된 모든 노드의 갯수를 알 수 있다.
결정적 깨달음		: 
오답 원인		: 1.
				  2.
*/////////////////////////////////////////////////////////////////////