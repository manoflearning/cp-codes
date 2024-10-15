// Bellman-Ford Algorithm

// INPUT: Given a directed gragh with weighted edges (possibly negative weight). Given a starting vertex.
// OUTPUT: Outputs the shortest distance from the starting vertex to all vertices.
// TIME COMPLEXITY: O(VE)

// BOJ 11657 AC Code
// https://www.acmicpc.net/problem/11657

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr first
#define sc second

const ll INF = 1e18;
int n, m;
vector<pair<ll, int>> adj[101010];
vector<ll> upper(101010, (ll)INF);
void input() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({ w, v });
	}
}

bool bellmanFord() {
  upper[1] = 0;
  int update = 1;
  for (int i = 0; i <= n; i++) {
    update = 0;
    for (int v = 1; v <= n; v++) {
      if (upper[v] == INF) continue;
      for (auto& i : adj[v]) {
        if (upper[i.sc] > upper[v] + i.fr) {
          upper[i.sc] = upper[v] + i.fr;
          update = 1;
        }
      }
    }
    if (!update) break;
  }
  return !update; // Returns false <=> The graph has a negative cycle.
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	input();

	if (bellmanFord()) {
		for (int i = 2; i <= n; i++) {
			if (upper[i] == INF) cout << -1 << '\n';
			else cout << upper[i] << '\n';
		}
	}
	else cout << -1 << '\n';

	return 0;
}
