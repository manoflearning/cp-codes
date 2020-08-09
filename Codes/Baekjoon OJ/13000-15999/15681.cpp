#include <iostream>
#include <vector>
using namespace std;

int N, R, Q;
vector<int> tree[(int)1e5 + 1];
int dp[(int)1e5 + 1];
//dp[i]는 i를 루트로 하는 서브트리에 속한 정점의 수

void dfs(int node, int last);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> R >> Q;

	for (int i = 0; i < N - 1; i++) {
		int a, b;
		cin >> a >> b;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}

	dfs(R, 0);

	while (Q--) {
		int node;
		cin >> node;

		cout << dp[node] << '\n';
	}

	return 0;
}

void dfs(int node, int last) {
	dp[node] = 1;
	for (int i = 0; i < tree[node].size(); i++) {
		if (tree[node][i] == last) continue;
		dfs(tree[node][i], node);
		dp[node] += dp[tree[node][i]];
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 트리 dp
접근 방식		:
결정적 깨달음		:
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////