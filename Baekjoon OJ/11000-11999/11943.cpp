#include <iostream>
using namespace std;

int main() {
	int a, b, c, d;

	scanf("%d %d %d %d", &a, &b, &c, &d);

	int ans = (a + d < b + c) ? a + d : b + c;

	printf("%d", ans);

	return 0;
}
/*
문제 해법		: 
접근 방식		:
결정적 깨달음		:
오답 원인		: 1. 
				  2.
*/
//////////////////////////////////////////////////////////////////////