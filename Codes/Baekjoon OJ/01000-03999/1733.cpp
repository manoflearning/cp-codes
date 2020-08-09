#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAX = 1e6;
const int INF = 1e9 + 7;

int N, A[MAX + 5], B[MAX + 5], dist[MAX + 5];
vector<int> adj[MAX + 5];
bool used[MAX + 5];

void input();
int hopcroft();
void bfs();
bool dfs(int a);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

	int total = hopcroft();

	if (total < N) cout << -1 << '\n';
	else {
		for (int i = 1; i <= N; i++) cout << A[i] << '\n';
	}

	return 0;
}

void input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		int a, b;
		cin >> a >> b;
		adj[i].push_back(a);
		adj[i].push_back(b);
	}
}

int hopcroft() {
	int ret = 0;
	memset(A, -1, sizeof(A));
	memset(B, -1, sizeof(B));
	while (true) {
		bfs();

		int flow = 0;
		for (int i = 1; i <= N; i++)
			if (!used[i] && dfs(i)) flow++;

		if (flow == 0) break;
		ret += flow;
	}
	return ret;
}

void bfs() {
	queue<int> q;
	for (int i = 1; i <= N; i++) {
		if (!used[i]) {
			dist[i] = 0;
			q.push(i);
		}
		else dist[i] = INF;
	}

	while (!q.empty()) {
		int a = q.front();
		q.pop();

		for (int b : adj[a]) {
			if (B[b] != -1 && dist[B[b]] == INF) {
				dist[B[b]] = dist[a] + 1;
				q.push(B[b]);
			}
		}
	}
}

bool dfs(int a) {
	for (int b : adj[a]) {
		if (B[b] == -1 || (dist[B[b]] == dist[a] + 1 && dfs(B[b]))) {
			used[a] = true;
			A[a] = b;
			B[b] = a;
			return true;
		}
	}
	return false;
}