#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

const int MAXV = 5 * 1e6;

int K, M, KpowM, res[2 * MAXV + 5], rTop;
int** adj, aTop[MAXV + 5];

void DFS(int v);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> K >> M;
	
	//예외 처리
	if (M == 1) {
		for (int v = 0; v < K; v++)
			cout << v << ' ';
		return 0;
	}
	
	KpowM = pow(K, M);

	//그래프 동적 할당
	adj = new int*[KpowM / K + 5];
	for (int i = 0; i < KpowM / K + 5; i++)
		adj[i] = new int[K];
	
	//그래프 만들기: k진수 연산
	for (int UtoV = 0; UtoV < KpowM; UtoV++) {
		int u = UtoV / K, v = UtoV % (KpowM / K);
		
		adj[u][aTop[u]++] = v;
	}

	//오일러 회로 찾기
	DFS(0);

	//예외 처리
	if (rTop - 1 != KpowM) {
		cout << -1;
		return 0;
	}
	
	//출력
	for (int v = rTop - 2; v >= 0; v--)
		cout << res[v] % K << ' ';

	//할당 해제
	for (int i = 0; i < KpowM / K + 5; i++)
		delete[] adj[i];
	delete[] adj;

	return 0;
}

void DFS(int v) {
	while (aTop[v] > 0) {
		DFS(adj[v][--aTop[v]]);
	}
	res[rTop++] = v;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 오일러 회로, k진수 연산
결정적 깨달음		:
시간복잡도		:
오답 원인		: 1.
				  2.
*/////////////////////////////////////////////////////////////////////