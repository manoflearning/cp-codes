#include <iostream>
using namespace std;

int main() {
	int t;
	scanf("%d", &t);

	for (int test = 0; test < t; test++) {
		int n, m;
		scanf("%d %d", &n, &m);

		if (n < 12 || m < 4) printf("-1\n");
		else printf("%d\n", m * 11 + 4);
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