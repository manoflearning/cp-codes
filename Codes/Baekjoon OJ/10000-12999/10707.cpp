#include <iostream>
using namespace std;

int main() {
	int a, b, c, d, p;

	scanf("%d %d %d %d %d", &a, &b, &c, &d, &p);

	int ans1 = a * p;
	int ans2 = b + ((p > c) ? (p - c) * d : 0);
	
	printf("%d", (ans1 < ans2) ? ans1 : ans2);

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