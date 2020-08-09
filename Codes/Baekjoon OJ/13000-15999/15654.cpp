#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
int arr[8];
vector<int> ans;
bool exist[8];

void backtrack();

int main() {
	cin >> n >> m;

	for (int i = 0; i < n; i++)
		cin >> arr[i];

	sort(arr, arr + n);

	backtrack();

	return 0;
}

void backtrack() {
	if (ans.size() == m) {
		for (int i = 0; i < m; i++)
			cout << ans[i] << ' ';
		cout << '\n';
	}

	for (int i = 0; i < n; i++) {
		if (exist[i]) continue;

		exist[i] = true;
		ans.push_back(arr[i]);

		backtrack();

		exist[i] = false;
		ans.pop_back();
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 백트래킹
접근 방식		: 수열 오름차순 정렬(사전순으로 출력해야 하기 때문) -> 중복 방지용 bool 배열로, 재귀 한번 호출 당 한 수씩 적함 -> 수열의 크기가 m이면 출력
결정적 깨달음		:
오답 원인		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////