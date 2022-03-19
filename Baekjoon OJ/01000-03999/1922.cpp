#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 1e5;

struct nnd {
	int n1, n2, d;
};

int N, M, p[MAX + 5];
nnd E[MAX + 5];

bool cmp(nnd a, nnd b) {
	return a.d < b.d;
}

int find(int x);
void merge(int a, int b);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	memset(p, -1, sizeof(p));

	cin >> N >> M;

	for (int i = 0; i < M; i++) {
		cin >> E[i].n1 >> E[i].n2 >> E[i].d;
	}
	//간선의 가중치를 기준으로 오름차순 정렬
	sort(E, E + M, cmp);

	int ans = 0;
	//간선을 차례로 순회
	for (int i = 0; i < M; i++) {
		//만약 간선의 두 정점이 같은 컴포넌트에 포함되어 있다면, 간선을 추가하지 않음.
		if (find(E[i].n1) == find(E[i].n2)) continue;
		ans += E[i].d;
		merge(E[i].n1, E[i].n2);
	}

	cout << ans;

	return 0;
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
문제 해법		: 최소 스패닝 트리, 크루스칼 알고리즘
결정적 깨달음		: 
시간복잡도		: O(|E|lg|E|)
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////