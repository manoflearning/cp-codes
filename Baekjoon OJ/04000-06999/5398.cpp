#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAX = 500;

struct xys {
	int x, y;
	string s;
};

int H, V, A[MAX + 5], B[MAX + 5];
xys wid[MAX + 5], hei[MAX + 5];
vector<int> adj[MAX + 5];
bool visited[MAX + 5];

void init();
void input();
void graph_modeling();
bool crash(int w, int h);
int bMatch();
bool dfs(int a);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int T; cin >> T;

	while (T--) {
		init();

		input();

		graph_modeling();

		int total = bMatch();
		//�ִ� ���� ������ �ּ� ���ؽ� Ŀ���� ������
		cout << H + V - total << '\n';
	}

	return 0;
}

void init() {
	for (int i = 0; i < MAX + 5; i++)
		adj[i].clear();
}

void input() {
	cin >> H >> V;

	for (int i = 0; i < H; i++)
		cin >> wid[i].x >> wid[i].y >> wid[i].s;
	for (int i = 0; i < V; i++)
		cin >> hei[i].x >> hei[i].y >> hei[i].s;
}

void graph_modeling() {
	for (int w = 0; w < H; w++) {
		for (int h = 0; h < V; h++) {
			if (crash(w, h)) adj[w].push_back(h);
		}
	}
}

bool crash(int w, int h) {
	if (wid[w].x <= hei[h].x && hei[h].x < wid[w].x + wid[w].s.size()) {
		if (hei[h].y <= wid[w].y && wid[w].y < hei[h].y + hei[h].s.size()) {
			if (wid[w].s[hei[h].x - wid[w].x] != hei[h].s[wid[w].y - hei[h].y]) return true;
		}
	 }
	return false;
}

int bMatch() {
	memset(A, -1, sizeof(A));
	memset(B, -1, sizeof(B));

	int ret = 0;
	for (int i = 0; i < H; i++) {
		memset(visited, 0, sizeof(visited));
		if (dfs(i)) ret++;
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
���� �ع�		: �ִ� ���� ����
������ ������		: ���� �ܾ�, ���� �ܾ �������� �ϴ� �� �׷����� �̷���� �̺� �׷��� ����. �浹�ϴ� �������� �������� ����. �ִ� ���� ������ �� ���ǻ� �������� �ʴ� �������� �ִ� ����. ���� �ִ� ���� ���� = ��.
�ð����⵵		: O(|V||E|)
���� ����		: 1.
				  2.
*///////////////////////////////////////////////////////////////////