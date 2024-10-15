#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr first
#define sc second

vector<pair<ll, int>> adj[202020];
vector<ll> dist(202020, (ll)1e18);
void dijkstra(int st) {
  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
  pq.push({0, st});
  dist[st] = 0;
  while (!pq.empty()) {
    auto [w, v] = pq.top();
    pq.pop();
    if (w > dist[v]) continue;
    for (auto &i : adj[v]) {
      if (dist[i.sc] > w + i.fr) {
        dist[i.sc] = w + i.fr;
        pq.push({w + i.fr, i.sc});
      }
    }
  }
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({ w, v });
	}
	int st, en;
	cin >> st >> en;

	dijkstra(st);

	cout << dist[en];
}