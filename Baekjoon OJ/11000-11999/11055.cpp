#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> A;
vector<int> dp;

int longest(int flag);

int main() {
	scanf("%d", &n);

	A.resize(n);
	dp.resize(n);

	for (int i = 0; i < n; i++)
		scanf("%d", &A[i]);

	int ret = 0;
	for (int i = 0; i < n; i++)
		ret = max(ret, longest(i));

	printf("%d", ret);

	return 0;
}

int longest(int flag) {
	//memoization
	if (dp[flag] != 0) return dp[flag];
	//
	for (int i = flag + 1; i < n; i++) {
		if (A[i] > A[flag]) {
			dp[flag] = max(dp[flag], longest(i));
		}
	}
	dp[flag] += A[flag];

	return dp[flag];
}

/*
문제 해법		: 동적 프로그래밍
접근 방식		:
결정적 깨달음	:
오답 원인		: 1. 
				  2.
*/