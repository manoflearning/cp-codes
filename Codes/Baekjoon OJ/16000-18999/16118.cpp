#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXV = 4 * 1e3;
const int INF = 1e9 + 7;

struct dn {
	double d; int n;
};
struct cmp {
	bool operator() (dn a, dn b) {
		return a.d > b.d;
	}
};
struct dns {
	double d; int n;
	bool s;
};
struct cmp2 {
	bool operator() (dns a, dns b) {
		return a.d > b.d;
	}
};

int N;
double fox[MAXV + 5], wolf[MAXV + 5][2];
vector<dn> adj[MAXV + 5];

void fox_min();
void wolf_min();

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	for (int i = 0; i < MAXV + 5; i++)
		fox[i] = wolf[i][0] = wolf[i][1] = INF;

	int M;
	cin >> N >> M;

	//양방향 그래프 형성
	for (int i = 0; i < M; i++) {
		int a, b; double d;
		cin >> a >> b >> d;
		adj[a].push_back({ d, b });
		adj[b].push_back({ d, a });
	}

	//여우와 늑대의 시간 계산
	fox_min();
	wolf_min();

	//각 그루터기마다 여우가 늑대보다 먼저 도착할 수 있는지 여부를 판별
	int cnt = 0;
	for (int i = 2; i <= N; i++) {
		if (fox[i] < min(wolf[i][0], wolf[i][1])) cnt++;
	}

	cout << cnt;

	return 0;
}

void fox_min() {
	priority_queue<dn, vector<dn>, cmp> pq;
	pq.push({ 0, 1 });
	fox[1] = 0;

	while (!pq.empty()) {
		double d = pq.top().d;
		int n = pq.top().n;
		pq.pop();

		if (fox[n] < d) continue;

		for (dn next : adj[n]) {
			if (fox[next.n] > d + next.d) {
				fox[next.n] = d + next.d;
				pq.push({ d + next.d, next.n });
			}
		}
	}
}
void wolf_min() {
	priority_queue<dns, vector<dns>, cmp2> pq;
	pq.push({ 0, 1, false });
	wolf[1][false] = 0;

	while (!pq.empty()) {
		double d = pq.top().d;
		int n = pq.top().n;
		bool s = pq.top().s;
		pq.pop();

		if (wolf[n][s] < d) continue;

		for (dn next : adj[n]) {
			double dist = d;
			if (!s) dist += next.d / 2;
			else dist += next.d * 2;

			if (wolf[next.n][!s] > dist) {
				wolf[next.n][!s] = dist;
				pq.push({ wolf[next.n][!s], next.n, !s });
			}
		}
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 다익스트라 알고리즘
결정적 깨달음		: 늑대의 최단경로 배열을 정점에 늑대가 뛰어온 경우와, 체력을 회복한 경우로 나누어 생각. dp 기법
시간복잡도		: O(|E|lg|E|)
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////