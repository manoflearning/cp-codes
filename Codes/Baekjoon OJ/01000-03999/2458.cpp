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
문제 해법		: 플로이드 와샬 알고리즘
결정적 깨달음		: 두 개의 그래프를 운용. 두 그래프 모두에서 경로가 없는 정점이 존재하는 정점은 답이 아님.
시간복잡도		: O(|V|^3)
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////