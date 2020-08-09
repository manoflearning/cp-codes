#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> arr;

void backtrack(int flag);

int main() {
	cin >> n >> m;

	backtrack(1);

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

	for (int i = flag; i <= n; i++) {
		arr.push_back(i);
		backtrack(i);
		arr.pop_back();
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 백트래킹
접근 방식		: 
결정적 깨달음		: 
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////