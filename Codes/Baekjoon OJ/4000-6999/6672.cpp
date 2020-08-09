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

		//시작
		int N, M;
		cin >> N >> M;

		if (N == 0 && M == 0) break;

		for (int i = 0; i < M; i++) {
			int a, b; 
			cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}

		//dfs 트리
		int cCnt = 0; //컴포넌트 세기
		for (int v = 0; v < N; v++) {
			if (dfsn[v] == -1) {
				dfs(v);
				cCnt++;
			}
		}

		//출력
		cout << cCnt + maxBcc - 1 << '\n';
	}

	return 0;
}

int dfs(int now, int prv) {
	int ret = dfsn[now] = ++dCnt, mBcc = 0;

	int child = 0;
	for (int next : adj[now]) {
		if (next == prv) continue;

		//역방향 간선
		if (dfsn[next] != -1) ret = min(ret, dfsn[next]);
		//트리 간선
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
문제 해법		: bcc
결정적 깨달음		: 
시간복잡도		: O(|V| + |E|)
오답 원인		: 1. 컴포넌트의 정점이 하나일 경우, 그 정점을 제외하면 출력값이 줄어듦
				  2. 
*/////////////////////////////////////////////////////////////////////