#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

struct xyr {
	int x, y, r;
};
struct nnd {
	int n1, n2;
	double d;
};

int W, N, p[1005];
vector<xyr> S;
vector<nnd> E;

bool cmp(nnd a, nnd b) {
	return a.d < b.d;
}
double dist(int u, int v);
int find(int x);
void merge(int u, int v);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	cout << fixed; cout.precision(6);

	int T; cin >> T;

	while (T--) {
		//reset
		memset(p, -1, sizeof(p));
		E.clear(); S.clear();

		//테스트케이스 시작
		cin >> W >> N;

		S.resize(N);

		for (int i = 0; i < N; i++)
			cin >> S[i].x >> S[i].y >> S[i].r;

		//센서와 센서 간의 간선
		for (int u = 0; u < S.size(); u++) {
			for (int v = u + 1; v < S.size(); v++) {
				E.push_back({ u, v, dist(u, v) });
			}
		}

		//벽과 센서 간의 간선
		for (int u = 0; u < S.size(); u++) {
			E.push_back({ u, N, (double)max(0, S[u].x - S[u].r) });
			E.push_back({ u, N + 1, (double)max(0, W - (S[u].x + S[u].r)) });
		}

		//벽과 벽 간의 간선
		E.push_back({ N, N + 1, (double)W });

		//간선들을 가중치를 기준으로 오름차순 정렬
		sort(E.begin(), E.end(), cmp);

		double ans = 0;
		for (int i = 0; i < E.size(); i++) {
			if (find(E[i].n1) == find(E[i].n2)) continue;
			ans = max(ans, E[i].d);
			merge(E[i].n1, E[i].n2);
			if (find(N) == find(N + 1)) break;
		}

		//반지름이므로 2로 나눠준다
		cout << ans / 2 << '\n';
	}

	return 0;
}

double dist(int u, int v) {
	double d = sqrt(pow(S[u].x - S[v].x, 2) + pow(S[u].y - S[v].y, 2));
	return max((double)0, d - (S[u].r + S[v].r));
}
int find(int x) {
	if (p[x] < 0) return x;
	p[x] = find(p[x]);
	return p[x];
}
void merge(int u, int v) {
	int U = find(u), V = find(v);
	if (U == V) return;
	p[U] += p[V];
	p[V] = U;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 크루스칼 알고리즘
결정적 깨달음		: 
시간복잡도		: 
오답 원인		: 1. 벽과 벽 간의 간선을 추가하지 않음 (센서의 개수가 0일 경우 틀림)
				  2. 
*/////////////////////////////////////////////////////////////////////