#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 1000;

vector<int> graph[MAX + 1];
bool visited[MAX + 1];

void dfs(int node);
void bfs(int node);

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	//입력
	int n, m, v;
	cin >> n >> m >> v;
	//입력 및 그래프 생성
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;

		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	//정점 번호가 작은 것을 먼저 방문하기 위해, 정렬
	for (int i = 1; i <= n; i++)
		sort(graph[i].begin(), graph[i].end());
	//dfs
	dfs(v);
	cout << '\n';
	//bfs
	memset(visited, 0, sizeof(visited));
	bfs(v);

	return 0;
}

void dfs(int node) {
	visited[node] = true;
	cout << node << ' ';

	for (int i = 0; i < graph[node].size(); i++) {
		if (visited[graph[node][i]]) continue;

		dfs(graph[node][i]);
	}
}
void bfs(int node) {
	queue<int> q;
	q.push(node);
	visited[node] = true;

	while (!q.empty()) {
		cout << q.front() << ' ';

		for (int i = 0; i < graph[q.front()].size(); i++)
			if (!visited[graph[q.front()][i]]) {
				q.push(graph[q.front()][i]);
				visited[graph[q.front()][i]] = true;
			}

		q.pop();
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: dfs와 bfs
접근 방식		: dfs와 bfs를 구현한다
결정적 깨달음		:
오답 원인		: 1.
				  2.
*/////////////////////////////////////////////////////////////////////