#include <iostream>
using namespace std;

int main() {
	long long int n;
	scanf("%lld", &n);

	long long int sum = 0;

	for (int flag = 1; flag < n; flag++)
		sum += flag * n + flag;

	printf("%lld", sum);

	return 0;
}
/*
문제 해법		: 수식 유도
접근 방식		:
결정적 깨달음		:
오답 원인		: 1. 
				  2.
*/
//////////////////////////////////////////////////////////////////////