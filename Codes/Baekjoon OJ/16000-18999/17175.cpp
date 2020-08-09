#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> dp;

int count(int n);

int main() {
	scanf("%d", &n);

	dp.resize(n + 1);

	printf("%d", count(n));

	return 0;
}

int count(int n) {
	//memoization
	if (dp[n] != 0) return dp[n];
	//base case
	if (n < 2) return 1;
	//
	dp[n] = 1;
	dp[n] += count(n - 1) + count(n - 2);

	dp[n] %= 1000000007;

	return dp[n];
}
/*
문제 해법		: dynamic programming, applied fibonacci
접근 방식		:
결정적 깨달음		:
오답 원인		: 1. 
				  2.
*/
///////////////////////////////////////////////////////////////////////
//help code to solve a problem