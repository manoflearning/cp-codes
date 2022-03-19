#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
int arr[500];

vector<int> dp;

int LIS(int flag);

int main() {
	int t;
	scanf("%d", &t);

	for (int test = 0; test < t; test++) {
		scanf("%d", &n);

		dp.resize(n, -1);

		for (int i = 0; i < n; i++)
			scanf("%d", &arr[i]);

		int ans = 0;
		for (int i = 0; i < n; i++)
			ans = max(ans, LIS(i));

		printf("%d\n", ans);

		dp.clear();
	}

	return 0;
}

int LIS(int flag) {
	//base case
	if (flag == n - 1) return 1;

	int& ret = dp[flag];
	//memoization
	if (ret != -1) return ret;

	ret = 1;

	for (int i = flag; i < n; i++)
		if (arr[i] > arr[flag]) ret = max(ret, LIS(i) + 1);

	return ret;
}
/*
문제 해법		: 
접근 방식		: 
결정적 깨달음		: 
오답 원인		: 1. 
				  2. 
*/
