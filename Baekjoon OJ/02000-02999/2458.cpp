#include <iostream>
#include <algorithm>
using namespace std;

const int MAXV = 500;
const int INF = 1e9 + 7;

int N, small[MAXV + 5][MAXV + 5], big[MAXV + 5][MAXV + 5];

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	for (int i = 0; i < MAXV + 5; i++) {
		fill(small[i], small[i] + MAXV + 5, INF);
		fill(big[i], big[i] + MAXV + 5, INF);
	}

	int M; 
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int a, b; cin >> a >> b;
		big[a][b] = small[b][a] = 1;
	}

	for (int i = 1; i <= N; i++)
		big[i][i] = small[i][i] = 0;

	for (int k = 1; k <= N; k++) {
		for (int u = 1; u <= N; u++) {
			for (int v = 1; v <= N; v++) {
				big[u][v] = min(big[u][v], big[u][k] + big[k][v]);
				small[u][v] = min(small[u][v], small[u][k] + small[k][v]);
			}
		}
	}

	int ans = 0;
	for (int u = 1; u <= N; u++) {
		ans++;
		for (int v = 1; v <= N; v++) {
			if (big[u][v] == INF && small[u][v] == INF) {
				ans--;
				break;
			}
		}
	}

	cout << ans;

	return 0;
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: �÷��̵� �ͼ� �˰�����
������ ������		: �� ���� �׷����� ���. �� �׷��� ��ο��� ��ΰ� ���� ������ �����ϴ� ������ ���� �ƴ�.
�ð����⵵		: O(|V|^3)
���� ����		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////