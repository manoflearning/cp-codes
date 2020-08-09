#include <iostream>
#include <vector>
using namespace std;

const int MAX = 1000000;

int n, m;
vector<int> p(MAX + 1, -1);

void merge(int b, int c);
int find(int x);

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;

		if (a == 0) merge(b, c);
		if (a == 1) {
			if (find(b) == find(c)) cout << "YES\n";
			else cout << "NO\n";
		}
	}

	return 0;
}

void merge(int b, int c) {
	int B = find(b), C = find(c);

	if (B != C) p[C] = B;
}
int find(int x) {
	if (p[x] < 0) return x;
	p[x] = find(p[x]);
	return p[x];
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 유니온 파인드
접근 방식		: 유니온 파인드의 find 연산의 시간복잡도는 O(log*N)로 상수시간으로 취급해도 좋다.
결정적 깨달음		: 유니온 파인드의 find 연산에서 매번 탐색이 이루어지는 루트 노드가 아닌 트리의 노드를, 루트 노드의 자식으로 연결해야 함. 그렇지 않으면 find 연산은 선형 시간복잡도를 가짐.
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////