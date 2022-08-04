#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <stack>
#include <algorithm>
using namespace std;

const int MAXV = 2 * 1e4;

int dfsn[MAXV + 5], dCnt, sNum[MAXV + 5], sCnt;
bool finished[MAXV + 5];
vector<int> adj[MAXV + 5];
stack<int> stk;

inline int trans(int x);
int dfs(int now);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	memset(dfsn, -1, sizeof(dfsn));

	int N, M;
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		adj[trans(-a)].push_back(trans(b));
		adj[trans(-b)].push_back(trans(a));
	}

	//dfs Ʈ��
	for (int v = 0; v < 2 * N; v++)
		if (dfsn[v] == -1) dfs(v);

	//xi�� ~xi�� ���� scc�� �ִٸ� 0 ���, �׷��� �ʴٸ� 1 ���
	bool yes = true;
	for (int v = 0; v < 2 * N; v += 2) {
		if (sNum[v] == sNum[v + 1]) {
			yes = false;
			break;
		}
	}

	if (yes) cout << 1;
	else cout << 0;

	return 0;
}

inline int trans(int x) {
	return (x > 0) ? 2 * (x - 1) : 2 * (-x - 1) + 1;
}

int dfs(int now) {
	int ret = dfsn[now] = ++dCnt;

	stk.push(now);

	for (int next : adj[now]) {
		if (dfsn[next] == -1) ret = min(ret, dfs(next));
		else if (!finished[next]) ret = min(ret, dfsn[next]);
	}

	if (ret >= dfsn[now]) {
		while (true) {
			int t = stk.top();
			stk.pop();

			sNum[t] = sCnt;
			finished[t] = true;

			if (t == now) break;
		}
		sCnt++;
	}

	return ret;
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: 2-SAT
������ ������		:
�ð����⵵		: O(|V| + |E|)
���� ����		: 1.
				  2.
*/////////////////////////////////////////////////////////////////////