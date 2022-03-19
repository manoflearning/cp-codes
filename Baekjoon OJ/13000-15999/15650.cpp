#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> arr;

void backtrack(int flag);

int main() {
	cin >> n >> m;

	backtrack(0);

	return 0;
}

void backtrack(int flag) {
	//base case
	if (arr.size() == m) {
		for (int i = 0; i < arr.size(); i++)
			cout << arr[i] << ' ';
		cout << '\n';

		return;
	}

	for (int i = flag + 1; i <= n; i++) {
		arr.push_back(i);
		backtrack(i);
		arr.pop_back();
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 백트래킹
접근 방식		: 현재까지 고른 수 중 가장 큰 수를 저장. 그 수보다 큰 수에 한해 탐색 수행
결정적 깨달음		: 
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////