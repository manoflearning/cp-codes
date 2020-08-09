#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int MAX = 1000;

vector<pair<int, int>> bus[MAX + 1];
int path[MAX + 1];

void shortestPath(int start, int end);

int main() {
	int n, m;
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int s, e, v;
		cin >> s >> e >> v;

		bus[s].push_back({ v, e });
	}

	int start, end;
	cin >> start >> end;

	for (int i = 1; i <= n; i++)
		path[i] = INT_MAX;

	shortestPath(start, end);

	return 0;
}

void shortestPath(int start, int end) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	pq.push({ 0, start });

	while (!pq.empty()) {
		int v = pq.top().first, e = pq.top().second;

		if (e == end) {
			cout << v;
			break;
		}

		if (v < path[e]) {
			path[e] = v;

			for (int i = 0; i < bus[e].size(); i++)
				pq.push({ v + bus[e][i].first, bus[e][i].second });
		}

		pq.pop();
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 다익스트라 알고리즘
접근 방식		: 음이 아닌 가중치의 그래프에서 한 정점으로부터 연결된 모든 정점까지의 최단거리를 구할 수 있다.
결정적 깨달음		:
오답 원인		: 1. 런타임에러. 배열의 크기를 MAX + 1로 선언해야 했음
				  2.
*/////////////////////////////////////////////////////////////////////