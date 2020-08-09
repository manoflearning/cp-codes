#include <iostream>
#include <cmath>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

int n;
vector< vector<int> > city;

long long int dp[16][65536];

long long int path(int start, int count, vector<bool>& checker);

int checker_cal(vector<bool>& checker);

int main() {
	scanf("%d", &n);

	city.resize(n, vector<int>(n));

	for (int i = 0; i < n; i++)
		for (int l = 0; l < n; l++) {
			//scanf(" %c", &city[i][l]);
			cin >> city[i][l];
		}
	
	vector<bool> checker(n, true);
	printf("%lld", path(0, 0, checker));

	return 0;
}

long long int path(int start, int count, vector<bool>& checker) {
	int cal = checker_cal(checker);
	//memoization
	if (dp[start][cal] != 0) return dp[start][cal];
	//base case
	if (count == n - 1) {
		if (city[start][0] != 0) return city[start][0];
		else return INT_MAX;
	}
	//
	dp[start][cal] = INT_MAX;

	for (int i = 1; i < n; i++) {
		if (!checker[i] || city[start][i] == 0) continue;
		
		checker[i] = false;
		dp[start][cal] = min(dp[start][cal], path(i, count + 1, checker) + city[start][i]);
		checker[i] = true;
	}

	return dp[start][cal];
}

int checker_cal(vector<bool>& checker) {
	int cal = 0;
	for (int i = 0; i < n; i++) {
		if (checker[i]) cal += pow(2, i);
	}
	return cal;
}
/*
문제 해법		: 동적 프로그래밍(외판원 순회)
접근 방식		:
결정적 깨달음	: 
오답 원인		: 1. 
				  2.
*/
//////////////////////////////////////////////////////////////////////
