#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXV = 1e5;

//강한 연결 요소용
int N, st, en;
int label[MAXV + 5], labelCnt;
int SCCnum[MAXV + 5], SCCcnt;
vector<int> adj[MAXV + 5];
stack<int> S;
bool finished[MAXV + 5];
vector<vector<int>> SCC;

//다익스트라용
struct dn {
	int d, n;
};
struct cmp {
	bool operator() (dn a, dn b) {
		return a.d < b.d;
	}
};
vector<int> SCCadj[MAXV + 5];
int dist[MAXV + 5];

int DFS(int v);
void find_max();

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	memset(label, -1, sizeof(label));
	memset(dist, -1, sizeof(dist));

	int M;
	cin >> N >> M >> st >> en;

	for (int i = 0; i < M; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
	}

	//dfs 스패닝 트리
	for (int v = 1; v <= N; v++)
		if (label[v] == -1) DFS(v);

	//scc 그래프 형성
	for (int v = 1; v <= N; v++) {
		for (int next : adj[v]) {
			int SCCv = SCCnum[v], SCCnext = SCCnum[next];
			if (SCCv == SCCnext) continue;
			SCCadj[SCCv].push_back(SCCnext);
		}
	}
	st = SCCnum[st], en = SCCnum[en];

	//다익스트라
	find_max();

	//출력
	cout << max(0, dist[en]);

	return 0;
}

int DFS(int v) {
	label[v] = labelCnt++;
	S.push(v);

	int ret = label[v];
	for (int next : adj[v]) {
		if (label[next] == -1) ret = min(ret, DFS(next));
		else if (!finished[next]) ret = min(ret, label[next]);
	}

	if (ret == label[v]) {
		vector<int> vSCC;
		while (true) {
			int t = S.top();
			S.pop();

			vSCC.push_back(t);
			SCCnum[t] = SCCcnt;
			finished[t] = true;

			if (t == v) break;
		}

		SCC.push_back(vSCC);
		SCCcnt++;
	}

	return ret;
}

void find_max() {
	priority_queue<dn, vector<dn>, cmp> pq;
	pq.push({ (int)SCC[st].size(), st });
	dist[st] = SCC[st].size();

	while (!pq.empty()) {
		int d = pq.top().d, n = pq.top().n;
		pq.pop();
		
		if (d < dist[n]) continue;
		//if (n == en) break;
		
		for (int next : SCCadj[n]) {
			if (dist[next] < d + (int)SCC[next].size()) {
				dist[next] = d + SCC[next].size();
				pq.push({ dist[next], next });
			}
		}
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: SCC + 정점에 가중치가 있을 때의 최장거리 구하기
결정적 깨달음		: SCC 그래프는 DAG이기 때문에, 최장거리를 구할 때 한 SCC를 두 번 방문할 수 없음
시간복잡도		: O(|V| + |E|lg|E|)
오답 원인		: 1.
				  2.
*/////////////////////////////////////////////////////////////////////