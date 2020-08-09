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
		//최대 독립 집합은 최소 버텍스 커버의 여집합
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
문제 해법		: 최대 독립 집합
결정적 깨달음		: 가로 단어, 세로 단어를 기준으로 하는 두 그룹으로 이루어진 이분 그래프 형성. 충돌하는 정점들을 간선으로 연결. 최대 독립 집합은 그 정의상 인접하지 않는 정점들의 최대 집합. 따라서 최대 독립 집합 = 답.
시간복잡도		: O(|V||E|)
오답 원인		: 1.
				  2.
*///////////////////////////////////////////////////////////////////