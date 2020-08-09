#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 1000;

int N, M, A[MAX + 5], B[MAX + 5];
vector<int> adj[MAX + 5];
bool visited[MAX + 5];

void init();
void scan();
int bMatch();
bool dfs(int a);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T; cin >> T;

	while (T--) {
		init();

		scan();

		int ans = bMatch();
		cout << ans << '\n';
	}

	return 0;
}

void init() {
	memset(A, -1, sizeof(A));
	memset(B, -1, sizeof(B));
	for (int i = 0; i < MAX + 5; i++)
		adj[i].clear();
}

void scan() {
	cin >> N >> M;

	for (int i = 1; i <= M; i++) {
		int a, b;
		cin >> a >> b;
		for (int l = a; l <= b; l++) {
			adj[i].push_back(l);
		}
	}
}

int bMatch() {
	int ret = 0;
	for (int i = 1; i <= M; i++) {
		//아직 매칭되지 않은 그룹 A의 정점에 대해 매칭 시도
		//if (A[i] == -1) {
			memset(visited, 0, sizeof(visited));
			if (dfs(i)) ret++;
		//}
	}
	return ret;
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
결정적 깨달음		:
시간복잡도		: O(N^3)
오답 원인		: 1.
				  2.
*///////////////////////////////////////////////////////////////////