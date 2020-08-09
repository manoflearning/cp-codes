#include <iostream>
using namespace std;

const int MAX = 2000;
const int MOD = 1000000007;

long long dp[MAX + 1][MAX + 1];

int main() {
	int n, cs, cf;
	cin >> n >> cs >> cf;

	dp[0][0] = 1;
	int f = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			if (i == cs || i == cf) dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % MOD;
			else dp[i][j] = (dp[i - 1][j + 1] * j + dp[i - 1][j - 1] * (j - f)) % MOD;
		}
		if (i == cs || i == cf) f++;
	}

	cout << dp[n][1];

	return 0;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 
접근 방식		: 
결정적 깨달음		: 
오답 원인		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////