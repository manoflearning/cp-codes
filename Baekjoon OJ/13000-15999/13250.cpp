#include <iostream>
using namespace std;

const int MAX = 1000000;

double dp[MAX];

double average(int x);

int main() {
	int n;
	cin >> n;

	printf("%.9lf", average(n));

	return 0;
}

double average(int x) {
	//base case
	if (x <= 0) return 0;

	double& ret = dp[x];
	//memoization
	if (ret != 0) return ret;

	ret += average(x - 1) + 1;
	ret += average(x - 2) + 1;
	ret += average(x - 3) + 1;
	ret += average(x - 4) + 1;
	ret += average(x - 5) + 1;
	ret += average(x - 6) + 1;

	ret /= 6;

	return ret;
}
/*//////////////////////////////////////////////////////////////////////
문제 해법		: 동적계획법
접근 방식		: 
결정적 깨달음		: 
오답 원인		: 1. 
				  2. 
*///////////////////////////////////////////////////////////////////////