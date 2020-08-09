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
���� �ع�		: �̺� ��Ī
������ ������		: A �׷��� �ð� ����, B �׷��� ���� ����. �̺� ��Ī�� ������ ������ N�� �Ǵ� ���� ����.
�ð����⵵		: O(N^3)
���� ����		: 1. 
				  2.
*///////////////////////////////////////////////////////////////////