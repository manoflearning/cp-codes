#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 1e7;

struct nnd {
	int n1, n2, d;
};

int N, M, p[(int)1e5 + 5];
nnd E[MAX + 5];

bool cmp(nnd a, nnd b);
int find(int x);
void merge(int a, int b);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	memset(p, -1, sizeof(p));

	cin >> N >> M;

	for (int i = 0; i < M; i++)
		cin >> E[i].n1 >> E[i].n2 >> E[i].d;
	
	sort(E, E + M, cmp);

	int cost = 0, mx = 0;

	for (int i = 0; i < M; i++) {
		if (find(E[i].n1) == find(E[i].n2)) continue;
		mx = max(mx, E[i].d);
		cost += E[i].d;
		merge(E[i].n1, E[i].n2);
	}

	cout << cost - mx;

	return 0;
}

bool cmp(nnd a, nnd b) {
	return a.d < b.d;
}
int find(int x) {
	if (p[x] < 0) return x;
	p[x] = find(p[x]);
	return p[x];
}
void merge(int a, int b) {
	int A = find(a), B = find(b);
	if (A == B) return;
	p[A] += p[B];
	p[B] = A;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 크루스칼 알고리즘
결정적 깨달음		: 마을을 두 개의 분리된 마을로 분할하기 위해서는, 일단 MST를 만들고, MST에서 가장 가중치가 큰 간선을 제거하면 된다.
시간복잡도		: O(|E|lg|E|)
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////