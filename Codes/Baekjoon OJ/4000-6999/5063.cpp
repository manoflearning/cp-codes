#include <iostream>
using namespace std;

int main() {
	int t;
	scanf("%d", &t);

	for (int test = 0; test < t; test++) {
		int r, e, c;
		scanf("%d %d %d", &r, &e, &c);

		if (e - c > r) printf("advertise\n");
		else if (e - c < r) printf("do not advertise\n");
		else printf("does not matter\n");
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