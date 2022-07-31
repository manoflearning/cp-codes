#include <iostream>
#include <map>
using namespace std;

map<int, int> bst;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int a, b;
	cin >> a >> b;
	
	for (int i = 0; i < a; i++) {
		int x;
		cin >> x;

		bst.insert({ x, 0 });
	}

	int ans = 0;

	for (int i = 0; i < b; i++) {
		int x;
		cin >> x;

		if (bst.find(x) != bst.end()) ans++;
	}

	cout << a + b - 2 * ans;

	return 0;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 이진 탐색 트리
접근 방식		: 균형잡힌 이진 탐색 트리를 활용하면 O(lgn)시간에 탐색 가능.
결정적 깨달음		: 
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////