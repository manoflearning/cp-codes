#include <iostream>
#include <cstring>
using namespace std;

const int MOD = 1000000000;

int n;
int dp[101][(1 << 11)][10];

int howmany(int digit, int visited, int last);

int main() {
	memset(dp, -1, sizeof(dp));

	cin >> n;

	int ans = 0;
	for (int i = 1; i <= 9; i++) {
		ans += howmany(2, (1 << i), i);
		ans %= MOD;
	}

	cout << ans;

	return 0;
}

int howmany(int digit, int visited, int last) {
	//base case
	if (digit == n + 1) {
		if (visited == (1 << 10) - 1) return 1;
		else return 0;
	}

	int& ret = dp[digit][visited][last];
	//memoization
	if (ret != -1) return ret;

	ret = 0;
	
	if (last - 1 >= 0)
		ret += howmany(digit + 1, visited | (1 << last - 1), last - 1);
	if (last + 1 <= 9)
		ret += howmany(digit + 1, visited | (1 << last + 1), last + 1);

	return ret %= MOD;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 동적계획법, 비트마스크
접근 방식		: 
결정적 깨달음		: 
오답 원인		: 1. 
				  2. 
*/////////////////////////////////////////////////////////////////////