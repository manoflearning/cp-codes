#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXV = 1e3;

int N, W;
vector<int> adj[MAXV + 5], indeg(MAXV + 5), cost(MAXV + 5), ans(MAXV + 5), result;

void topological_sort();

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T; cin >> T;

	while (T--) {
		for (int i = 0; i < MAXV + 5; i++) {
			adj[i].clear();
			indeg[i] = cost[i] = ans[i] = 0;
		}
		result.clear();

		//테스트케이스 시작
		int M;
		cin >> N >> M;

		for (int v = 1; v <= N; v++) {
			cin >> cost[v];
			ans[v] = cost[v];
		}

		for (int i = 0; i < M; i++) {
			int a, b; cin >> a >> b;
			adj[a].push_back(b);
			indeg[b]++;
		}

		cin >> W;

		//위상 정렬
		topological_sort();

		//시간 계산
		for (int i = 0; i < result.size(); i++) {
			int v = result[i];
			for (int next : adj[v])
				ans[next] = max(ans[next], ans[v] + cost[next]);
			if (v == W) break;
		}

		cout << ans[W] << '\n';
	}

	return 0;
}

void topological_sort() {
	queue<int> q;

	for (int v = 1; v <= N; v++)
		if (indeg[v] == 0) q.push(v);

	for(int i=0; i<N; i++) {
		int v = q.front();
		q.pop();

		result.push_back(v);

		for (int next : adj[v]) {
			indeg[next]--;
			if (indeg[next] == 0) q.push(next);
		}
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 위상 정렬
결정적 깨달음		: 
시간복잡도		: O(|V| + |E|)
오답 원인		: 1.
				  2.
*/////////////////////////////////////////////////////////////////////