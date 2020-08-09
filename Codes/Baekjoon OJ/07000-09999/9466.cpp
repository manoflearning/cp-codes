#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAXV = 1e5;

vector<int> adj[MAXV + 5];
bool visited[MAXV + 5], finished[MAXV + 5];
int ans;

void init();
void dfs(int now);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T; cin >> T;

	while (T--) {
		init();

		int N; cin >> N;

		ans = N;

		for (int u = 1; u <= N; u++) {
			int v; cin >> v;
			adj[u].push_back(v);
		}
		
		for (int i = 1; i <= N; i++) {
			if (!visited[i]) dfs(i);
		}

		cout << ans << '\n';
	}

	return 0;
}

void init() {
	for (auto& i : adj) i.clear();
	memset(visited, 0, sizeof(visited));
	memset(finished, 0, sizeof(finished));
}

void dfs(int now) {
	visited[now] = true;
	for (int next : adj[now]) {
		if (!visited[next]) dfs(next);
		else if (!finished[next]) {
			for (int i = next; i != now; i = adj[i][0]) ans--;
			ans--;
		}
	}
	finished[now] = true;
}