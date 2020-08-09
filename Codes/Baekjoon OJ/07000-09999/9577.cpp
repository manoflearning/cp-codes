#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAX = 100;

int N, A[MAX + 5], B[MAX + 5];
vector<int> adj[MAX + 5];
bool visited[MAX + 5];

void init();
void input();
int bMatch();
bool dfs(int a);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T; cin >> T;

	while (T--) {
		init();
		
		input();

		int ans = bMatch();
		cout << ans << '\n';
	}

	return 0;
}

void init() {
	for (int i = 0; i < MAX + 5; i++)
		adj[i].clear();
}

void input() {
	int M;
	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		int a, b, cnt;
		cin >> a >> b >> cnt;
		while (cnt--) {
			int x; cin >> x;
			for (int i = a + 1; i <= b; i++)
				adj[i].push_back(x);
		}
	}
}

int bMatch() {
	memset(A, -1, sizeof(A));
	memset(B, -1, sizeof(B));

	int total = 0;
	for (int i = 1; i <= MAX; i++) {
		memset(visited, 0, sizeof(visited));
		if (dfs(i)) total++;

		if (total == N) return i;
	}
	return -1;
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
결정적 깨달음		: A 그룹은 시간 정점, B 그룹은 조각 정점. 이분 매칭을 돌리다 유량이 N이 되는 순간 멈춤.
시간복잡도		: O(N^3)
오답 원인		: 1. 
				  2.
*///////////////////////////////////////////////////////////////////