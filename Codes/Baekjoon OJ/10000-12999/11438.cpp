#include <iostream>
#include <vector>
using namespace std;

const int MAX = 1e5;

vector<int> adj[MAX + 5];
int par[MAX + 5], sz[MAX + 5];
vector<int> chain[MAX + 5];
int depth[MAX + 5], chain_num[MAX + 5], chain_idx[MAX + 5];

int dfs(int now, int prv);
void HLD(int now, int prv, int num, int d);
int LCA(int u, int v);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N; cin >> N;

	for (int i = 0; i < N - 1; i++) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	dfs(1, 0);
	
	HLD(1, 0, 1, 0);
	
	int M; cin >> M;

	while (M--) {
		int u, v;
		cin >> u >> v;

		cout << LCA(u, v) << '\n';
	}

	return 0;
}

int dfs(int now, int prv) {
	par[now] = prv;
	sz[now] = 1;
	for (int next : adj[now]) {
		if (next != prv) sz[now] += dfs(next, now);
	}
	return sz[now];
}

void HLD(int now, int prv, int num, int d) {
	depth[now] = d;
	chain_idx[now] = chain[num].size();
	chain_num[now] = num;

	chain[num].push_back(now);

	int heavy = -1;
	for (int next : adj[now]) {
		if (next != prv && (heavy == -1 || sz[next] > sz[heavy])) heavy = next;
	}

	if (heavy != -1) HLD(heavy, now, num, d);

	for (int next : adj[now]) {
		if (next != prv && next != heavy)
			HLD(next, now, next, d + 1);
	}
}

int LCA(int u, int v) {
	while (chain_num[u] != chain_num[v]) {
		if (depth[u] > depth[v]) u = par[chain_num[u]];
		else v = par[chain_num[v]];
	}
	return chain_idx[u] > chain_idx[v] ? v : u;
}