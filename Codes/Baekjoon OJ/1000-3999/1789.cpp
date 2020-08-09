#include <iostream>
using namespace std;

const int max_n = 93000;

long long int s;

long long int b_search(int left = 0, int right = max_n);

int main() {
	scanf("%lld", &s);

	printf("%d", b_search());

	return 0;
}

long long int b_search(int left, int right) {
	long long int flag = (left + right) / 2;
	
	long long int sum1 = (flag + 1) * flag / 2;
	long long int sum2 = (flag + 2) * (flag + 1) / 2;

	if (sum1 <= s && s < sum2) return flag;
	if (sum1 > s) return b_search(left, flag);
	if (sum2 < s) return b_search(flag + 1, right);
}
/*
문제 해법		: 가우스덧셈, 이진탐색
접근 방식		:
결정적 깨달음	: 
오답 원인		: 1. lower bound 구현 오류
				  2.
*/
//////////////////////////////////////////////////////////////////////
