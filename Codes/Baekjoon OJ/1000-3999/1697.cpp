#include <iostream>
#include <queue>
using namespace std;

const int MAX = 100000;

bool visited[MAX + 1];

int main() {
	int n, k;
	cin >> n >> k;

	queue<pair<int, int>> q;
	q.push(make_pair(n, 0));
	visited[n] = true;
	
	int ans;
	while (true) {
		int x = q.front().first, v = q.front().second;
		if (x == k) {
			ans = v;
			break;
		}

		if (x > 0 && !visited[x - 1]) {
			q.push(make_pair(x - 1, v + 1));
			visited[x - 1] = true;
		}
		if (x < MAX && !visited[x + 1]) {
			q.push(make_pair(x + 1, v + 1));
			visited[x + 1] = true;
		}
		if (2 * x <= MAX && !visited[2 * x]) {
			q.push(make_pair(2 * x, v + 1));
			visited[2 * x] = true;
		}

		q.pop();
	}

	cout << ans;
	
	return 0;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: bfs
접근 방식		: 노드 x에 대해 x - 1, x + 1, 2 * x와 연결된 그래프가 주어져 있다고 생각. BFS 적용. 최단거리 구함. BFS로 최단거리룰 구할 수 있음.
결정적 깨달음		: 
오답 원인		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////