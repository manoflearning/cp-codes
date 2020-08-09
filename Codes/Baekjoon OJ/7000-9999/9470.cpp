#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXV = 1e3;

int N;
vector<int> adj[MAXV + 5], ans(MAXV + 5), order;
stack<int> stk;
map<int, int> cost[MAXV + 5];
bool visited[MAXV + 5];

void topological_sort();
void dfs(int v);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T; cin >> T;

	while (T--) {
		fill(ans.begin(), ans.end(), 1);
		memset(visited, 0, sizeof(visited));
		for (int i = 0; i < MAXV + 5; i++) {
			adj[i].clear(); cost[i].clear();
		}
		order.clear();

		//테스트케이스 시작
		int K, M;
		cin >> K >> N >> M;

		for (int i = 0; i < M; i++) {
			int a, b; cin >> a >> b;
			adj[a].push_back(b);
		}

		topological_sort();

		for (int i = 0; i < order.size(); i++) {
			int v = order[i];
			for (int next : adj[v]) {
				map<int, int>::iterator it = cost[next].find(ans[v]);
				
				if (it != cost[next].end()) {
					ans[next] = max(ans[next], ans[v] + 1);
				}
				else {
					cost[next].insert({ ans[v], ans[v] });
					ans[next] = max(ans[next], ans[v]);
				}
			}
		}

		cout << K << ' ' << ans[N] << '\n';
	}

	return 0;
}

void topological_sort() {
	for (int v = 1; v <= N; v++)
		if (!visited[v]) dfs(v);

	while (!stk.empty()) {
		order.push_back(stk.top());
		stk.pop();
	}
}
void dfs(int v) {
	visited[v] = true;
	for (int next : adj[v]) {
		if (visited[next]) continue;
		dfs(next);
	}
	stk.push(v);
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 위상 정렬
결정적 깨달음		:
시간복잡도		: O(|E|lg|E|)
오답 원인		: 1. dfs의 중복 방지 if 문을 if (visited[next])가 아닌 if (visited[v])로 입력함. 내가 흔히 하는 실수.
				  2.
*/////////////////////////////////////////////////////////////////////