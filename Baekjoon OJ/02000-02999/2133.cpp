#include <iostream>
#include <algorithm>

int n;
long long int dp[31];

long long int dynamic(int count);

int main() {
	scanf("%d", &n);

	if (n % 2 == 0) printf("%d", dynamic(n));
	else printf("0");

	return 0;
}

long long int dynamic(int count) {
	//base case, memoization
	if (count == 0) return 1;
	if (dp[count] != 0) return dp[count];
	//
	dp[count] += 3 * dynamic(count - 2);

	for (int i = 4; i <= count; i += 2) {
		dp[count] += 2 * dynamic(count - i);
	}

	return dp[count];
}

/*
���� �ع�		: ���� ���α׷���
���� ���		:
������ ������	:
���� ����		: 1. 
				  2.
*/