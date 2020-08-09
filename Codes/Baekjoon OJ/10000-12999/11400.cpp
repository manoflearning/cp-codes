#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXV = 1e5;

struct nn {
	int n1, n2;
};

int dfsn[MAXV + 5], dCnt;
vector<int> adj[MAXV + 5];
map<pair<int, int>, int> aEdges;

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

	//dfs 트리
	for (int v = 1; v <= N; v++)
		if (dfsn[v] == -1) dfs(v);

	//출력
	cout << aEdges.size() << '\n';
	for (map<pair<int, int>, int>::iterator it = aEdges.begin(); it != aEdges.end(); it++)
		cout << it->first.first << ' ' << it->first.second << '\n';

	return 0;
}

int dfs(int now, int prv) {
	int ret = dfsn[now] = ++dCnt, child = 0;
	
	for (int next : adj[now]) {
		if (next == prv) continue;

		//트리 간선
		if (dfsn[next] == -1) {
			child++;
			int nRet = dfs(next, now);
			ret = min(ret, nRet);
			
			if (nRet > dfsn[now])
				aEdges.insert({ { min(now, next), max(next, now) }, 0 });
		}
		//역방향 간선
		else ret = min(ret, dfsn[next]);
	}

	return ret;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 이중 연결 요소, 단절선
결정적 깨달음		: 
시간복잡도		: O(|V| + |E|)
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////