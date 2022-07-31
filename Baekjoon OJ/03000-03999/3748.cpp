#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;

#define pii pair<int, int>

const int MAXV = 1e5;

int dfsn[MAXV + 5], dCnt, depth[MAXV + 5];
vector<int> adj[MAXV + 5];
vector<map<pii, int>> bcc;
stack<pii> stk;
map<int, int> ans;

void reset();
int dfs(int now, int prv = -1);
bool bfs(map<pii, int>& edges);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T; cin >> T;

	while (T--) {
		reset();

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

		//bcc별로 bfs하여 홀수 길이의 사이클 찾기
		for (int i = 0; i < bcc.size(); i++) {
			if (bfs(bcc[i])) {
				map<pii, int>::iterator it;
				for (it = bcc[i].begin(); it != bcc[i].end(); it++) {
					ans.insert({ it->first.first, 0 });
					ans.insert({ it->first.second, 0 });
				}
			}
		}

		//출력
		cout << ans.size() << '\n';
	}

	return 0;
}

void reset() {
	memset(dfsn, -1, sizeof(dfsn));
	dCnt = 0;
	memset(depth, -1, sizeof(depth));
	for (int i = 0; i < MAXV + 5; i++)
		adj[i].clear();
	bcc.clear();
	ans.clear();
}

int dfs(int now, int prv) {
	int ret = dfsn[now] = ++dCnt;

	for (int next : adj[now]) {
		if (next == prv) continue;

		if (dfsn[now] > dfsn[next]) stk.push(pii(now, next));

		if (dfsn[next] != -1) ret = min(ret, dfsn[next]);
		else {
			int tmp = dfs(next, now);
			ret = min(ret, tmp);

			if (tmp >= dfsn[now]) {
				map<pii, int> nowBcc;
				while (true) {
					pii t = stk.top();
					stk.pop();

					nowBcc.insert({ { min(t.first, t.second), max(t.first, t.second) }, 0 });

					if (t == pii(now, next)) break;
				}

				bcc.push_back(nowBcc);
			}
		}
	}

	return ret;
}

bool bfs(map<pii, int>& edges) {
	bool ret = false;

	queue<int> q;
	q.push(edges.begin()->first.first);
	depth[edges.begin()->first.first] = 1;

	while (!q.empty()) {
		int now = q.front();
		q.pop();

		for (int next : adj[now]) {
			//bcc에 포함되지 않는 간선일 경우 배제
			map<pii, int>::iterator it = edges.find(pii(min(now, next), max(now,next)));
			if (it == edges.end()) continue;

			//방문하지 않은 정점일 경우
			if (depth[next] == -1) {
				depth[next] = depth[now] + 1;
				q.push(next);
			}
			//이미 방문한 정점일 경우
			else if (depth[now] == depth[next]) ret = true;
		}
	}

	map<pii, int>::iterator it;
	for (it = edges.begin(); it != edges.end(); it++)
		depth[it->first.first] = depth[it->first.second] = -1;

	return ret;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: bcc
결정적 깨달음		: bcc에 홀수 사이클이 있다면, bcc의 모든 정점은 정답에 포함됨. 그렇지 않다면, 단절점을 제외한 bcc의 모든 정점은 정답에 포함되지 않음.
시간복잡도		: O(|E|lg|E|)
오답 원인		: 1.
				  2.
*/////////////////////////////////////////////////////////////////////