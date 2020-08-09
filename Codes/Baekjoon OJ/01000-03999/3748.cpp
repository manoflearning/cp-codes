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

		//dfs Ʈ��
		for (int v = 1; v <= N; v++)
			if (dfsn[v] == -1) dfs(v);

		//bcc���� bfs�Ͽ� Ȧ�� ������ ����Ŭ ã��
		for (int i = 0; i < bcc.size(); i++) {
			if (bfs(bcc[i])) {
				map<pii, int>::iterator it;
				for (it = bcc[i].begin(); it != bcc[i].end(); it++) {
					ans.insert({ it->first.first, 0 });
					ans.insert({ it->first.second, 0 });
				}
			}
		}

		//���
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
			//bcc�� ���Ե��� �ʴ� ������ ��� ����
			map<pii, int>::iterator it = edges.find(pii(min(now, next), max(now,next)));
			if (it == edges.end()) continue;

			//�湮���� ���� ������ ���
			if (depth[next] == -1) {
				depth[next] = depth[now] + 1;
				q.push(next);
			}
			//�̹� �湮�� ������ ���
			else if (depth[now] == depth[next]) ret = true;
		}
	}

	map<pii, int>::iterator it;
	for (it = edges.begin(); it != edges.end(); it++)
		depth[it->first.first] = depth[it->first.second] = -1;

	return ret;
}
/*////////////////////////////////////////////////////////////////////
���� �ع�		: bcc
������ ������		: bcc�� Ȧ�� ����Ŭ�� �ִٸ�, bcc�� ��� ������ ���信 ���Ե�. �׷��� �ʴٸ�, �������� ������ bcc�� ��� ������ ���信 ���Ե��� ����.
�ð����⵵		: O(|E|lg|E|)
���� ����		: 1.
				  2.
*/////////////////////////////////////////////////////////////////////