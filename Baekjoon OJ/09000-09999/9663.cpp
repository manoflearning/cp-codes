#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAX = 15;

int n;
vector<pair<int, int>> queen;
int ans;

void backtrack(int s_y);
bool canAttack(int y, int x);

int main() {
	cin >> n;

	backtrack(-1);

	cout << ans;

	return 0;
}

void backtrack(int s_y) {
	//base case
	if (queen.size() == n) {
		ans++;
		return;
	}
	//
	for (int x = 0; x < n; x++) {
		if (canAttack(s_y + 1, x)) continue;

		queen.push_back({ s_y + 1, x });
		backtrack(s_y + 1);
		queen.pop_back();
	}
}
bool canAttack(int y, int x) {
	for (int i = 0; i < queen.size(); i++) {
		//같은 가로줄에 위치
		if (x == queen[i].second) return true;
		//기울기가 1
		if ((int)fabs(y - queen[i].first) == (int)fabs(x - queen[i].second)) return true;
	}

	return false;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 백트래킹
접근 방식		:
결정적 깨달음		:
오답 원인		: 1. 과하게 많은 재귀호출을 사용함
				  2.
*/////////////////////////////////////////////////////////////////////