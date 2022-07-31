#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct pdn {
	int p, d, n;
};
struct cmp {
	bool operator() (pdn a, pdn b) {
		return a.d > b.d;
	}
};

int N, M, K, dist[101][10001];
vector<pdn> adj[101];
bool visited[101][10001];

void reset();
void shortestPath();

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T; cin >> T;

	while (T--) {
		reset();
		
		cin >> N >> M >> K;

		for (int i = 0; i < K; i++) {
			int u, v, c, d;
			cin >> u >> v >> c >> d;
			adj[u].push_back({ c, d, v });
		}

		shortestPath();

		int ans = 1000 * 100 + 1;
		for (int i = 0; i < 10001; i++)
			ans = min(ans, dist[N][i]);

		if (ans == 1000 * 100 + 1) cout << "Poor KCM\n";
		else cout << ans << '\n';
	}

	return 0;
}

void reset() {
	for (int i = 0; i < 101; i++) {
		for (int l = 0; l < 10001; l++) {
			dist[i][l] = 1000 * 100 + 1;
			visited[i][l] = false;
		}
		adj[i].clear();
	}
}
void shortestPath() {
	priority_queue<pdn, vector<pdn>, cmp> pq;
	pq.push({ M, 0, 1 });

	while (!pq.empty()) {
		int p = pq.top().p, d = pq.top().d, n = pq.top().n;
		pq.pop();

		if (dist[n][p] < d) continue;

		for (pdn next : adj[n]) {
			if (p - next.p >= 0 && dist[next.n][p - next.p] > d + next.d) {
				dist[next.n][p - next.p] = d + next.d;
				pq.push({ p - next.p, d + next.d, next.n });
			}
		}
	}
}
/*void shortestPath() {
	priority_queue<pdn, vector<pdn>, cmp> pq;
	pq.push({ M, 0, 1 });

	while (!pq.empty()) {
		int p = pq.top().p, d = pq.top().d, n = pq.top().n;
		pq.pop();

		if (dist[n][p] < d) continue;

		dist[n][p] = d;
		visited[n][p] = true;

		for (pdn next : adj[n]) {
			if (p - next.p >= 0 && !visited[next.n][p - next.p]) {
				pq.push({ p - next.p, d + next.d, next.n });
			}
		}
	}
}*/
/*////////////////////////////////////////////////////////////////////
문제 해법		: 다익스트라 알고리즘
결정적 깨달음		: 
시간복잡도		: O(mElgV)
오답 원인		: 1. 중복 검사는 우선순위 큐에 삽입 연산을 할 때 해야 함. 그렇지 않으면 불필요한 메모리와 연산이 소비됨.
				  2. 
*/////////////////////////////////////////////////////////////////////