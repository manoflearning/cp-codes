#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <stack>
#define pii pair<int, int>
using namespace std;

const int MAXV = 2 * 1e4;

int N, dfsn[MAXV + 5], dCnt, sNum[MAXV + 5], sCnt, ans[MAXV / 2 + 5];
vector<int> adj[MAXV + 5];
stack<int> stk;
bool finished[MAXV + 5];
pii p[MAXV + 5];

inline int trans(int x);
int dfs(int now);
void print();

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	memset(dfsn, -1, sizeof(dfsn));
	memset(ans, -1, sizeof(ans));

	int M;
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		adj[trans(-a)].push_back(trans(b));
		adj[trans(-b)].push_back(trans(a));
	}

	//scc
	for (int v = 0; v < 2 * N; v++)
		if (dfsn[v] == -1) dfs(v);

	//충족 가능성 판별
	for (int v = 0; v < 2 * N; v += 2) {
		if (sNum[v] == sNum[v + 1]) {
			cout << 0;
			return 0;
		}
	}

	//답 출력
	cout << 1 << '\n';

	print();

	return 0;
}

inline int trans(int x) {
	return (x > 0) ? 2 * (x - 1) : 2 * (-x - 1) + 1;
}

int dfs(int now) {
	int ret = dfsn[now] = ++dCnt;

	stk.push(now);

	for (int next : adj[now]) {
		if (dfsn[next] == -1) ret = min(ret, dfs(next));
		else if (!finished[next]) ret = min(ret, dfsn[next]);
	}

	if (ret >= dfsn[now]) {
		while (true) {
			int t = stk.top();
			stk.pop();

			sNum[t] = sCnt;
			finished[t] = true;

			if (t == now) break;
		}
		sCnt++;
	}

	return ret;
}

void print() {
	for (int v = 0; v < 2 * N; v++)
		p[v] = pii(sNum[v], v);

	sort(p, p + 2 * N);

	for (int i = 2 * N - 1; i >= 0; i--) {
		int v = p[i].second;

		if (ans[v / 2 + 1] == -1) ans[v / 2 + 1] = (v % 2) ? 1 : 0;
	}

	for (int v = 1; v <= N; v++)
		cout << ans[v] << ' ';
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 2-SAT
결정적 깨달음		: scc의 순서는 위상 정렬의 역순.
시간복잡도		: O(|V| + |E|)
오답 원인		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////