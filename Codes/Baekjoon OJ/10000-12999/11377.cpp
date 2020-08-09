#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 1000;
const int MAXV = 2 * MAX;

int N, M, K;
int A[MAXV + 5], B[MAX + 5];
vector<int> adj[MAXV + 5];
bool visited[MAXV + 5];

void input();
int bMatch();
bool dfs(int a);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

	int ans = bMatch();
	cout << ans << '\n';

	return 0;
}

void input() {
	cin >> N >> M >> K;

	for (int i = 1; i <= N; i++) {
		int cnt; cin >> cnt;
		while (cnt--) {
			int x; cin >> x;
			adj[2 * i - 1].push_back(x);
			adj[2 * i].push_back(x);
		}
	}
}

int bMatch() {
	memset(A, -1, sizeof(A));
	memset(B, -1, sizeof(B));
	int ret = 0;
	for (int i = 1; i <= 2 * N; i += 2) {
		memset(visited, 0, sizeof(visited));
		if (dfs(i)) ret++;
	}

	int mxK = 0;
	for (int i = 2; i <= 2 * N; i += 2) {
		memset(visited, 0, sizeof(visited));
		if (dfs(i)) mxK++;
	}

	return ret + min(mxK, K);
}

bool dfs(int a) {
	visited[a] = true;
	for (int b : adj[a]) {
		if (B[b] == -1 || (!visited[B[b]] && dfs(B[b]))) {
			A[a] = b;
			B[b] = a;
			return true;
		}
	}
	return false;
}
/*//////////////////////////////////////////////////////////////////
문제 해법		: 이분 매칭
결정적 깨달음		: 각 직원마다 정점을 2개로 분할한다. 직원별 첫번째 정점을 대상으로 이분 매칭을 수행한다. 직원별 두번째 정점을 대상으로 이분 매칭을 수행하는데, 이때 최댓값은 K이다.
시간복잡도		: O(|V||E|)
오답 원인		: 1.
				  2.
*///////////////////////////////////////////////////////////////////