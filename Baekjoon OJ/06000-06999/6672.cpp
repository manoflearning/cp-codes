#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXV = 1e4;

int dfsn[MAXV + 5], dCnt, maxBcc;
vector<int> adj[MAXV + 5];

int dfs(int now, int prv = -1);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	while (true) {
		dCnt = maxBcc = 0;
		memset(dfsn, -1, sizeof(dfsn));
		for (int i = 0; i < MAXV + 5; i++)
			adj[i].clear();

		//����
		int N, M;
		cin >> N >> M;

		if (N == 0 && M == 0) break;

		for (int i = 0; i < M; i++) {
			int a, b; 
			cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}

		//dfs Ʈ��
		int cCnt = 0; //������Ʈ ����
		for (int v = 0; v < N; v++) {
			if (dfsn[v] == -1) {
				dfs(v);
				cCnt++;
			}
		}

		//���
		cout << cCnt + maxBcc - 1 << '\n';
	}

	return 0;
}

int dfs(int now, int prv) {
	int ret = dfsn[now] = ++dCnt, mBcc = 0;

	int child = 0;
	for (int next : adj[now]) {
		if (next == prv) continue;

		//������ ����
		if (dfsn[next] != -1) ret = min(ret, dfsn[next]);
		//Ʈ�� ����
		else {
			int tmp = dfs(next, now);
			ret = min(ret, tmp);

			child++;

			if (prv != -1 && tmp >= dfsn[now]) mBcc++;
		}
	}

	if (prv == -1) {
		if (child >= 2) maxBcc = max(maxBcc, child);
	}
	else maxBcc = max(maxBcc, mBcc + 1);

	return ret;
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: bcc
������ ������		: 
�ð����⵵		: O(|V| + |E|)
���� ����		: 1. ������Ʈ�� ������ �ϳ��� ���, �� ������ �����ϸ� ��°��� �پ��
				  2. 
*/////////////////////////////////////////////////////////////////////