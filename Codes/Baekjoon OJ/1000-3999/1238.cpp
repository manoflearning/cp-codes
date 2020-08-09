#include <iostream>
#include <algorithm>
using namespace std;

const int MAXV = 1e3;
const int INF = 1e9 + 7;

int N, X, adj[MAXV + 5][MAXV + 5];

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	for (int i = 0; i < MAXV + 5; i++)
		fill(adj[i], adj[i] + MAXV + 5, INF);

	int M;
	cin >> N >> M >> X;

	for (int i = 0; i < M; i++) {
		int a, b, c; 
		cin >> a >> b >> c;
		adj[a][b] = min(adj[a][b], c);
	}

	for (int i = 1; i <= N; i++) adj[i][i] = 0;

	for (int k = 1; k <= N; k++) {
		for (int u = 1; u <= N; u++) {
			if (adj[u][k] == INF) continue;
			for (int v = 1; v <= N; v++) {
				adj[u][v] = min(adj[u][v], adj[u][k] + adj[k][v]);
			}
		}
	}

	int ans = -1;
	for (int v = 1; v <= N; v++)
		ans = max(ans, adj[v][X] + adj[X][v]);

	cout << ans;

	return 0;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 플로이드의 모든 정점쌍 최단 경로 알고리즘
결정적 깨달음		: adj[u][k] == INF인 경우 v for문을 돌리지 않아 시간 단축
시간복잡도		: O(n^3)
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////