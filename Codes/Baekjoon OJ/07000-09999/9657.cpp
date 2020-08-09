#include <iostream>
#include <cstring>
using namespace std;

const int MAX = 1000;
const int SK = 0, CY = 1;

int dp[MAX + 1];

int who_win(int x);

int main() {
	memset(dp, -1, sizeof(dp));

	int n;
	cin >> n;

	who_win(n);

	if (dp[n] == SK) cout << "SK";
	else cout << "CY";

	return 0;
}

int who_win(int x) {
	//base case
	if (x <= 0) return -1;

	int& ret = dp[x];

	if (x == 1 || x == 3 || x == 4) return ret = SK;
	//memoization
	if (ret != -1) return ret;

	ret = CY;
	if (who_win(x - 1) == CY) ret = SK;
	if (who_win(x - 3) == CY) ret = SK;
	if (who_win(x - 4) == CY) ret = SK;

	return ret;
}
/*//////////////////////////////////////////////////////////////////////
���� �ع�		: dp.
���� ���		: 
������ ������		: 
���� ����		: 1. base case�� ������� �ʵ��� ������
				  2. 
*///////////////////////////////////////////////////////////////////////