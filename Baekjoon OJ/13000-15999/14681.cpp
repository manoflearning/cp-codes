#include <iostream>
using namespace std;

int main() {
	int x, y;

	scanf("%d %d", &x, &y);

	if (x > 0) {
		if (y > 0) printf("1");
		else printf("4");
	}
	else {
		if (y > 0) printf("2");
		else printf("3");
	}

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