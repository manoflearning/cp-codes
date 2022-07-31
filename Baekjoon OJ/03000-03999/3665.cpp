#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXV = 500;

int N, arr[MAXV + 5], indeg[MAXV + 5];
bool adj[MAXV + 5][MAXV + 5], isCycle, isMany;
vector<int> res;

void topological_sort();

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T; cin >> T;

	while (T--) {
		for (int i = 0; i < MAXV + 5; i++)
			memset(adj[i], 0, sizeof(adj[i]));
		memset(indeg, 0, sizeof(indeg));
		isCycle = isMany = false;
		res.clear();

		//테스트케이스 시작
		cin >> N;

		for (int i = 0; i < N; i++)
			cin >> arr[i];

		for (int i = 0; i < N; i++) {
			for (int l = i + 1; l < N; l++) {
				int u = arr[i], v = arr[l];
				adj[u][v] = true;
				indeg[v]++;
			}
		}

		int M; cin >> M;
		for (int i = 0; i < M; i++) {
			int u, v; cin >> u >> v;
			if (adj[u][v]) {
				indeg[v]--;
				indeg[u]++;
				swap(adj[u][v], adj[v][u]);
			}
			else {
				indeg[v]++;
				indeg[u]--;
				swap(adj[u][v], adj[v][u]);
			}
		}

		//위상 정렬
		topological_sort();

		//출력
		if (isCycle) cout << "IMPOSSIBLE\n";
		else if (isMany) cout << "?\n";
		else {
			for (int i = 0; i < res.size(); i++)
				cout << res[i] << ' ';
			cout << '\n';
		}
	}

	return 0;
}

void topological_sort() {
	queue<int> q;
	
	for (int v = 1; v <= N; v++)
		if (indeg[v] == 0) q.push(v);

	for (int i = 0; i < N; i++) {
		if (q.empty()) {
			isCycle = true;
			break;
		}
		if (q.size() > 1) isMany = true;

		int v = q.front();
		q.pop();

		res.push_back(v);

		for (int next = 1; next <= N; next++) {
			if (adj[v][next]) {
				indeg[next]--;
				if (indeg[next] == 0) q.push(next);
			}
		}
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 위상정렬
결정적 깨달음		:
시간복잡도		: O(|V|^2)
오답 원인		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////