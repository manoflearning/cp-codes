#include <iostream>
#include <vector>
using namespace std;

int n, m;
bool visited[9];
vector<int> arr;

void backtrack();

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

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
		if (visited[i]) continue;

		visited[i] = true;
		arr.push_back(i);

		backtrack();

		visited[i] = false;
		arr.pop_back();
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 백트래킹
접근 방식		: 수열의 첫번째 수를 정하고, 첫번째 수를 제외하고(중복 방지), 두번째 수를 정하고, 를 재귀적으로 반복
결정적 깨달음		: 
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////