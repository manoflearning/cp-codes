#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n;
	scanf("%d", &n);

	if (n == 1) printf("4");
	else if (n == 2) printf("6");
	else if (n == 3) printf("10");
	else {
		vector<long long int> dp(n);

		dp[0] = 1, dp[1] = 1;
		for (int i = 2; i < n; i++)
			dp[i] = dp[i - 1] + dp[i - 2];

		printf("%lld", 3 * dp[n - 1] + 2 * dp[n - 2] + 2 * dp[n - 3] + dp[n - 4]);
	}

	return 0;
}
/*
문제 해법		: 피보나치 수열 응용, 동적계획법 (bottom up)
접근 방식		:
결정적 깨달음	:
오답 원인		: 1. 출력 형식 (%d -> %lld)
				  2.
*/
///////////////////////////////////////////////////////////////////////