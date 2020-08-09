#include <iostream>
#include <vector>
using namespace std;

const int MAXV = 1e3;

int N, adj[MAXV + 5][MAXV + 5], degree[MAXV + 5], E;
vector<int> euler_circult;

void DFS(int now);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N;

	for (int u = 1; u <= N; u++) {
		for (int v = 1; v <= N; v++) {
			cin >> adj[u][v];
			degree[u] += adj[u][v];
			degree[v] += adj[u][v];
			E += adj[u][v];
		}
	}

	E /= 2;

	//오일러 회로 존재 여부 판별
	//모든 정점의 차수가 짝수 개 혹은 0개이고, 모든 간선이 하나의 컴포넌트에 포함되면 오일러 회로는 존재한다.
	//그렇지 않을경우 오일러 회로는 존재하지 않는다.
	for (int v = 1; v <= N; v++) {
		degree[v] /= 2;
		if (degree[v] % 2 != 0) {
			cout << -1;
			return 0;
		}
	}

	//dfs로 오일러 회로 구하기
	DFS(1);
	
	//모든 간선이 같은 컴포넌트에 있는가?
	if (euler_circult.size() != E + 1) cout << -1;
	else {
		for (int v : euler_circult)
			cout << v << ' ';
	}

	return 0;
}

void DFS(int now) {
	//인접행렬
	for(int next = 1; next <= N; next++)
		if (adj[now][next]) {
			adj[now][next]--;
			adj[next][now]--;
			DFS(next);
		}
	//경로의 역순으로 배열이 구성된다.
	euler_circult.push_back(now);
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 오일러 회로
결정적 깨달음		: 
시간복잡도		: O(|V||E|)
오답 원인		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////