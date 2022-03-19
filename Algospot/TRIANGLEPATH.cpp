#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
int triangle[100][100];

vector< vector<int> > dp;

int max_find(int y, int x);

int main() {
	int c;
	scanf("%d", &c);

	for (int test = 0; test < c; test++) {
		scanf("%d", &n);

		dp.resize(n, vector<int>(n, -1));

		for (int y = 0; y < n; y++)
			for (int x = 0; x <= y; x++) {
				scanf("%d", &triangle[y][x]);
			}

		printf("%d\n", max_find(0, 0));

		dp.clear();
	}
}

int max_find(int y, int x) {
	//base case
	if (y == n - 1) return triangle[y][x];

	int& ret = dp[y][x];
	//memoization
	if (ret != -1) return ret;

	ret = max(max_find(y + 1, x), max_find(y + 1, x + 1));
	ret += triangle[y][x];

	return ret;
}
/*
문제 해법		: 
접근 방식		: 
결정적 깨달음		: 
오답 원인		: 1. 
				  2. 
*/
//////////////////////////////////////////////////////////////////////
