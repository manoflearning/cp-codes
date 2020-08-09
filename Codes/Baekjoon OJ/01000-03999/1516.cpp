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

	//���� ����
	topological_sort();

	//���� ����� �������� �ּ� �ð� ���
	for (int i = 0; i < result.size(); i++) {
		int v = result[i];
		for (int next : adj[v])
			mCost[next] = max(mCost[next], cost[next] + mCost[v]);
	}

	//��� ���
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
���� �ع�		: ���� ����
������ ������		:
�ð����⵵		: O(|V| + |E|)
���� ����		: 1.
				  2.
*/////////////////////////////////////////////////////////////////////