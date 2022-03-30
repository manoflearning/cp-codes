#include <iostream>
#include <algorithm>
using namespace std;

const int MAXV = 250;
const int INF = 1e9 + 7;

int N, adj[MAXV + 5][MAXV + 5];

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	for (int i = 0; i < MAXV + 5; i++)
		fill(adj[i], adj[i] + MAXV + 5, INF);

	int M; 
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int u, v, b;
		cin >> u >> v >> b;

		adj[u][v] = 0;
		if (b == 0) adj[v][u] = min(adj[v][u], 1);
		else adj[v][u] = 0;
	}

	for (int i = 1; i <= N; i++) adj[i][i] = 0;

	for (int k = 1; k <= N; k++) {
		for (int u = 1; u <= N; u++) {
			for (int v = 1; v <= N; v++) {
				adj[u][v] = min(adj[u][v], adj[u][k] + adj[k][v]);
			}
		}
	}

	int Q; cin >> Q;

	while (Q--) {
		int u, v; cin >> u >> v;

		cout << adj[u][v] << '\n';
	}

	return 0;
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: �÷��̵� �ͼ� �˰�����
������ ������		: ���� �ܹ����� ���, ���� ������ ����ġ�� 0����, ������ ������ ����ġ�� 1�� �Ѵ�. ������� ��� ������ ����ġ�� 0�̴�.
�ð����⵵		: 
���� ����		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////