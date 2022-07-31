#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> arr;

void backtrack();

int main() {
	cin >> n >> m;

	backtrack();
	
	return 0;
}

void backtrack() {
	//base case
	if (arr.size() == m) {
		for (int i = 0; i < arr.size(); i++)
			cout << arr[i] << ' ';
		cout << '\n';

		return;
	}

	for (int i = 1; i <= n; i++) {
		arr.push_back(i);
		backtrack();
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