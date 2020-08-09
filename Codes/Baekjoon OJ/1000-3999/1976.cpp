#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> p(201, -1);

int find(int x);
void merge(int a, int b);

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	//입력 및 merge 연산을 활용해서 유향 트리 만들기
	cin >> n >> m;

	for (int c1 = 1; c1 <= n; c1++) {
		for (int c2 = 1; c2 <= n; c2++) {
			int x;
			cin >> x;

			if (x == 1) merge(c1, c2);
		}
	}
	//
	int wannaGo[1000];
	for (int i = 0; i < m; i++)
		cin >> wannaGo[i];

	bool ans = true;
	for (int i = 0; i < m - 1; i++)
		if (find(wannaGo[i]) != find(wannaGo[i + 1])) {
			ans = false;
			break;
		}

	if (ans) cout << "YES\n";
	else cout << "NO\n";

	return 0;
}

int find(int x) {
	if (p[x] < 0) return x;
	p[x] = find(p[x]);
	return p[x];
}
void merge(int a, int b) {
	int A = find(a), B = find(b);
	if (A != B) p[B] = A;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 유니온 파인드
접근 방식		: 입력을 받을 때 union 연산 활용(코드에선 merge함수). 가능 여부를 find 연산으로 판단.
결정적 깨달음		: 
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////