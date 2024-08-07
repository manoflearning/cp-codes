#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<pair<int, int>> adj[1010];
int st, en;
vector<int> dist(1010, 1e9 + 7);

struct State {
	int w, v;
	bool operator<(const State& rhs) const {
		return w > rhs.w;
	}
};

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({ w, v });
	}
	cin >> st >> en;

	priority_queue<State> pq;
	pq.push({ 0, st });
	dist[st] = 0;
	while (!pq.empty()) {
		auto [w, v] = pq.top();
		pq.pop();

		if (dist[v] < w) continue;

		for (auto& i : adj[v]) {
			if (w + i.first < dist[i.second]) {
				dist[i.second] = w + i.first;
				pq.push({ w + i.first, i.second });
			}
		}
	}

	cout << dist[en];
}