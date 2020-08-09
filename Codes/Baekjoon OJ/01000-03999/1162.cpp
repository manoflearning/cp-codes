#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#define ll long long
using namespace std;

const int MAX = 10000;

struct dn {
	ll d, n;
};
struct dnf {
	ll d, n, f;
};
struct cmp {
	bool operator() (dnf a, dnf b) {
		return a.d > b.d;
	}
};

ll N, M, K, dist[MAX + 5][21];
vector<dn> adj[MAX + 5];
bool visited[MAX + 5][21];

void shortestPath();

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	//reset
	for (int i = 0; i < MAX + 5; i++) {
		for (int l = 0; l < 21; l++)
			dist[i][l] = 1e13;
	}
	memset(visited, 0, sizeof(visited));

	cin >> N >> M >> K;

	for (int i = 0; i < M; i++) {
		ll n1, n2, d;
		cin >> n1 >> n2 >> d;
		adj[n1].push_back({ d, n2 });
		adj[n2].push_back({ d, n1 });
	}

	shortestPath();

	ll ans = 1e13;
	for (int i = 0; i < 21; i++) {
		ans = min(ans, dist[N][i]);
	}

	cout << ans;

	return 0;
}

void shortestPath() {
	priority_queue<dnf, vector<dnf>, cmp> pq;
	pq.push({ 0, 1, K });

	while (!pq.empty()) {
		ll d = pq.top().d, n = pq.top().n, f = pq.top().f;
		pq.pop();

		if (dist[n][f] < d) continue;

		dist[n][f] = d;
		visited[n][f] = true;

		for (dn next : adj[n]) {
			if (!visited[next.n][f]) {
				pq.push({ d + next.d, next.n, f });
			}
			if (f > 0 && !visited[next.n][f - 1]) {
				pq.push({ d, next.n, f - 1});
			}
		}
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 다익스트라 알고리즘 응용
결정적 깨달음		: 포장하지 않은 도로의 개수를 구분지어 다익스트라 알고리즘을 적용한다.
시간복잡도		: O(fElgV)
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////