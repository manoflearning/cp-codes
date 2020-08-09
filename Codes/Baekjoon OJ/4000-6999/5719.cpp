#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

const int MAX = 500;

struct dnp {
	//차례대로 st에서 n까지의 최단거리, 노드의 번호, 최단거리로 왔을 때 n 직전의 노드
	int d, n, p;
};
struct cmp {
	bool operator() (dnp a, dnp b) {
		return a.d > b.d;
	}
};

int N, M, st, en;
vector<pair<int, int>> adj[MAX];
int dist[MAX];
vector<int> prv[MAX];
bool cannot[MAX][MAX];

void shortestPath();
void DFS(int n);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	while (true) {
		memset(cannot, 0, sizeof(cannot));
		for (int i = 0; i < MAX; i++) {
			dist[i] = 1e9;
			adj[i].clear();
			prv[i].clear();
		}

		cin >> N >> M;

		if (N == 0 && M == 0) break;

		cin >> st >> en;

		for (int i = 0; i < M; i++) {
			int u, v, p;
			cin >> u >> v >> p;
			adj[u].push_back({ p, v });
		}

		shortestPath();
		DFS(en);
		
		for (int i = 0; i < MAX; i++)
			dist[i] = 1e9;

		shortestPath();

		if (dist[en] == 1e9) cout << "-1\n";
		else cout << dist[en] << '\n';
	}

	return 0;
}

void shortestPath() {
	bool visited[MAX];
	memset(visited, 0, sizeof(visited));

	priority_queue<dnp, vector<dnp>, cmp> pq;
	pq.push({ 0, st, -1 });
	visited[st] = true;

	while (!pq.empty()) {
		dnp now = pq.top();
		pq.pop();

		if (dist[now.n] < now.d) continue;

		dist[now.n] = now.d;
		prv[now.n].push_back(now.p);
		visited[now.n] = true;

		for (pair<int, int> next : adj[now.n]) {
			if (cannot[now.n][next.second] || visited[next.second]) continue;
			pq.push({ next.first + now.d, next.second, now.n });
		}
	}
}
void DFS(int n) {
	for (int p : prv[n]) {
		if (p == -1) continue;
		cannot[p][n] = true;
		DFS(p);
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 다익스트라 알고리즘, dfs
결정적 깨달음		: 
시간복잡도		: O(ElgV)
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////