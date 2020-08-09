#include <iostream>
#include <vector>
using namespace std;

int n, k;

vector< vector<int> > dp;

int sum_cal(int sum, int count);

int main() {
	scanf("%d %d", &n, &k);

	dp.resize(n + 1, vector<int>(k, -1));

	printf("%d", sum_cal(0, 0));

	return 0;
}

int sum_cal(int sum, int count) {
	//base case
	if (sum > n) return 0;
	if (count == k) {
		if (sum == n) return 1;
		else return 0;
	}
	//memoization
	if (dp[sum][count] != -1) return dp[sum][count];
	//
	dp[sum][count] = 0;

	for (int i = 0; i <= n; i++) {
		dp[sum][count] += sum_cal(sum + i, count + 1);
		dp[sum][count] %= 1000000000;
	}

	return dp[sum][count];
}
/*
문제 해법		: 동적 계획법(top down)
접근 방식		: 
결정적 깨달음	: 
오답 원인		: 1. 
				  2. 
*/
//////////////////////////////////////////////////////////////////////