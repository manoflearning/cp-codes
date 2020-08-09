#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int a, b, c;

	scanf("%d %d %d", &a, &b, &c);

	if (a > b) swap(a, b);
	if (b > c) swap(b, c);
	if (a > b) swap(a, b);

	printf("%d %d %d", a, b, c);

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