#include <iostream>
using namespace std;

int main() {
	int a, b;

	scanf("%d %d", &a, &b);

	int c;
	scanf("%d", &c);
	
	b += c % 60;
	if (b >= 60) {
		b %= 60;
		a += 1;
	}
	a += c / 60;
	a %= 24;

	printf("%d %d", a, b);

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