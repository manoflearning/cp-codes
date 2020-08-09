#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXV = 100;
const int INF = 1e9 + 7;

int N, M;
int adj[MAXV + 5][MAXV + 5], cost[MAXV + 5];
bool visited[MAXV + 5];
vector<int> ans;

int dfs(int v);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	for (int i = 0; i < MAXV + 5; i++)
		fill(adj[i], adj[i] + MAXV + 5, INF);

	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int a, b; cin >> a >> b;
		adj[a][b] = adj[b][a] = 1;
	}

	for (int i = 1; i <= N; i++) adj[i][i] = 0;

	for (int k = 1; k <= N; k++) {
		for (int u = 1; u <= N; u++) {
			for (int v = 1; v <= N; v++) {
				adj[u][v] = min(adj[u][v], adj[u][k] + adj[k][v]);
			}
		}
	}

	for (int u = 1; u <= N; u++) {
		for (int v = 1; v <= N; v++) {
			if (adj[u][v] < INF) {
				cost[u] = max(cost[u], adj[u][v]);
			}
		}
	}

	for (int u = 1; u <= N; u++) {
		if (!visited[u]) {
			ans.push_back(dfs(u));
		}
	}

	sort(ans.begin(), ans.end());

	cout << ans.size() << '\n';
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << '\n';

	return 0;
}

int dfs(int v) {
	visited[v] = true;

	int ret = v;
	for (int next = 1; next <= N; next++) {
		if (visited[next]) continue;
		if (adj[v][next] != 1) continue;

		int flag = dfs(next);
		if (cost[ret] > cost[flag])
			ret = flag;
	}

	return ret;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 플로이드 와샬 알고리즘 + dfs
결정적 깨달음		: dfs로 위원회 구별. 플로이드 와샬 알고리즘으로 각 위원회마다 모든 위원회 인물 쌍의 최단 거리를 구하고, 인물 기준으로 다 더함.
시간복잡도		: 
오답 원인		: 1. 의사결정시간의 합이 아닌, 의사결정시간의 최댓값을 구하는 문제
				  2. 
*/////////////////////////////////////////////////////////////////////