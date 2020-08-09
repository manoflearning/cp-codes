#include <iostream>
#include <algorithm>
using namespace std;

const int MAXV = 20;

int N, dist[MAXV + 5][MAXV + 5], adj[MAXV + 5][MAXV + 5];

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N;

	for (int u = 1; u <= N; u++) {
		for (int v = 1; v <= N; v++) {
			cin >> dist[u][v];
			adj[u][v] = dist[u][v];
		}
	}

	bool cannot = false;

	for (int u = 1; u <= N; u++) {
		//v = u + 1인 이유: 양방향 간선이기에 u에서 v까지의 최단경로는 v에서 u까지의 최단경로와 같음
		for (int v = u + 1; v <= N; v++) {
			for (int k = 1; k <= N; k++) {
				if (k == u || k == v) continue;
				//어떤 두 경로의 거리가 같을 경우, 경유점이 없는 경로가 아닌 경유점이 있는 경로를 택한다. 그것이 더 많은 정점 간의 경로를 규정하기 때문이다.
				if (dist[u][v] == dist[u][k] + dist[k][v]) {
					adj[u][v] = adj[v][u] = 0;
				}
				//dist[u][v]보다 dist[u][k] + dist[k][v]가 작다면, dist[u][v]가 최단거리가 아닌 것. 따라서 모순.
				else if (dist[u][v] > dist[u][k] + dist[k][v]) {
					cout << -1;
					return 0;
				}
			}
		}
	}
	
	
	int ans = 0;
	for (int u = 1; u <= N; u++) {
		for (int v = u + 1; v <= N; v++) {
			ans += adj[u][v];
		}
	}

	cout << ans;

	return 0;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 플로이드 와샬 알고리즘인가..?
결정적 깨달음		: 모든 정점 쌍에 대해, 그 최단 거리를 다른 정점 쌍의 최단거리의 합으로 표현 가능하다면 간선이 없는 것으로 한다.
시간복잡도		: O(|V|^3)
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////