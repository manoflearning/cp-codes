#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXV = 1e5;

int dfsn[MAXV + 5], dCnt;
vector<int> adj[MAXV + 5];
bool isCactus = true;

int dfs(int now, int prv = -1);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	memset(dfsn, -1, sizeof(dfsn));

	int N, M;
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	//dfs Ʈ��
	for (int v = 1; v <= N; v++)
		if (dfsn[v] == -1) dfs(v);

	//���
	if (isCactus) cout << "Cactus";
	else cout << "Not cactus";

	return 0;
}

int dfs(int now, int prv) {
	int ret = dfsn[now] = ++dCnt;

	int cycle = 0, upCycle = 0;
	//��Ʈ ����
	if (prv == -1) {
		for (int next : adj[now]) {
			if (next == prv) continue;

			//�湮�� �� �ִ� ����
			if (dfsn[next] != -1) {
				ret = min(ret, dfsn[next]);
			}
			//�湮�� �� ���� ����
			else {
				int tmp = dfs(next, now);
				ret = min(ret, tmp);

				if (tmp == dfsn[now]) cycle++;
			}
		}

		if (cycle >= 2) isCactus = false;
	}
	//��Ʈ ������ �ƴ� ����
	else {
		for (int next : adj[now]) {
			if (next == prv) continue;

			//�湮�� �� �ִ� ����
			if (dfsn[next] != -1) {
				ret = min(ret, dfsn[next]);
				if (dfsn[next] < dfsn[now]) upCycle++;
			}
			//�湮�� �� ���� ����
			 else {
				int tmp = dfs(next, now);
				ret = min(ret, tmp);

				if (tmp == dfsn[now]) cycle++;
				else if (tmp < dfsn[now]) upCycle++;
			}
		}

		if (cycle + upCycle >= 2) isCactus = false;
	}

	return ret;
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: ������ + ������
������ ������		: 
�ð����⵵		: O(|V| + |E|)
���� ����		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////