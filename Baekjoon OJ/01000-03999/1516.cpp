#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXV = 500;

int N;
vector<int> adj[MAXV + 5], indeg(MAXV + 5), result;
vector<int> cost(MAXV + 5), mCost(MAXV + 5);

void topological_sort();

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N;

	for (int v = 1; v <= N; v++) {
		cin >> cost[v];
		mCost[v] = cost[v];
		while (true) {
			int u; cin >> u;
			if (u == -1) break;
			adj[u].push_back(v);
			indeg[v]++;
		}
	}

	//위상 정렬
	topological_sort();

	//정렬 결과를 바탕으로 최소 시간 계산
	for (int i = 0; i < result.size(); i++) {
		int v = result[i];
		for (int next : adj[v])
			mCost[next] = max(mCost[next], cost[next] + mCost[v]);
	}

	//결과 출력
	for (int i = 1; i <= N; i++)
		cout << mCost[i] << '\n';

	return 0;
}

void topological_sort() {
	queue<int> q;

	for (int i = 1; i <= N; i++)
		if (indeg[i] == 0) q.push(i);

	for (int i = 0; i < N; i++) {
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