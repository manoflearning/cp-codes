#include <iostream>
using namespace std;

int main() {
	while (true) {
		int a, b;
		scanf("%d %d", &a, &b);

		if (a == 0 && b == 0) break;

		if (a <= b) printf("No\n");
		else printf("Yes\n");
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