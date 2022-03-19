#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

const int MAXV = 1e4;

int N, cnt = 1, dfsn[MAXV + 5], cntSCC, sn[MAXV + 5];
vector<int> adj[MAXV + 5];
vector<vector<int>> SCC;
stack<int> S;
bool finished[MAXV + 5];

int dfs(int v);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int M;
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
	}

	//dfs 스패닝 트리 생성
	for (int v = 1; v <= N; v++)
		if (dfsn[v] == 0) dfs(v);

	sort(SCC.begin(), SCC.end());

	//출력
	cout << cntSCC << '\n';
	for (int i = 0; i < SCC.size(); i++) {
		for (int v : SCC[i])
			cout << v << ' ';
		cout << "-1\n";
	}

	return 0;
}

int dfs(int v) {
	//방문 순서를 기준으로 labeled
	dfsn[v] = cnt++;
	S.push(v);

	int result = dfsn[v];
	for (int next : adj[v]) {
		//visited의 역할
		if (dfsn[next] == 0) result = min(result, dfs(next));
		else if (!finished[next]) result = min(result, dfsn[next]);
	}

	//조상 노드에게로 향하는 간선이 없을 때, v를 루트로 하는 서브트리는 SCC
	if (result == dfsn[v]) {
		vector<int> vSCC;

		while (true) {
			int t = S.top();
			S.pop();
			vSCC.push_back(t);
			finished[t] = true;
			sn[t] = cntSCC;
			if (t == v) break;
		}

		sort(vSCC.begin(), vSCC.end());

		SCC.push_back(vSCC);
		cntSCC++;
	}

	return result;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 강한 연결 요소
결정적 깨달음		: 
시간복잡도		: O(|V| + |E|)
오답 원인		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////