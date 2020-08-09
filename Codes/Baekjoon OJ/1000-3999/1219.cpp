#include <iostream>
#include <vector>
#define ll long long
using namespace std;

const int MAX = 100;
const ll INF = 1e11 + 7;

struct dv {
	ll d; int v;
};
struct vvd {
	int v1, v2; ll d;
};

int N, M, st, en;
vvd Q[MAX + 5];
ll VW[MAX + 5];
vector<ll> upper(MAX + 5, -INF);
vector<dv> adj[MAX + 5];
bool canGo[MAX + 5], cycle[MAX + 5];

void DFS(int v, bool arr[]);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> st >> en >> M;

	for (int i = 0; i < M; i++)
		cin >> Q[i].v1 >> Q[i].v2 >> Q[i].d;

	for (int i = 0; i < N; i++)
		cin >> VW[i];

	for (int i = 0; i < M; i++) {
		//원 문제는 최장거리를 구하는 문제이므로 값에 -를 붙여 최단거리를 구하는 문제로 바꿈
		//간선의 가중치에 도착 정점의 가중치를 더함.
		adj[Q[i].v1].push_back({ -Q[i].d + VW[Q[i].v2], Q[i].v2 });
	}

	upper[st] = VW[st];

	bool update;
	for (int i = 0; i < N ; i++) {
		update = false;
		for (int now = 0; now < N; now++) {
			for (dv next : adj[now]) {
				if (upper[now] != -INF && upper[next.v] < upper[now] + next.d) {
					upper[next.v] = upper[now] + next.d;
					update = true;

					//음수 싸이클에서 en 정점으로의 경로가 존재하는가 ?
					if (i == N - 1) DFS(now, cycle);
				}
			}
		}

		if (!update) break;
	}

	//시작점에서 en 정점으로의 경로가 존재하는가?
	if (upper[en] == -INF) cout << "gg";
	//음수 사이클에서 en 정점으로의 경로가 존재하는가?
	else if (cycle[en]) cout << "Gee";
	else cout << upper[en];

	return 0;
}

void DFS(int v, bool arr[]) {
	arr[v] = true;
	for (dv next : adj[v]) {
		if (arr[next.v]) continue;
		DFS(next.v, arr);
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 벨만-포드 알고리즘
결정적 깨달음		: 정점의 가중치가 주어진 상황에서 최단거리를 구할 때, 간선의 가중치에 정점의 가중치를 더해, 마치 정점의 가중치가 없는 것처럼 최단 거리 알고리즘을 적용할 수 있다.
시간복잡도		: O(|V||E|)
오답 원인		: 1. 답을 출력할 때, 시작점에서 도착점으로의 경로 여부를 가장 먼저 확인해야 함. 그 다음 음수 사이클에서 도착점으로의 경로 여부를 확인해야 함.
				  2. 도시의 수가 1일 경우를 고려하지 못함
				  3.
*/////////////////////////////////////////////////////////////////////