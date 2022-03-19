#include <iostream>
using namespace std;

int main() {
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);

	while (k > 0) {
		if (n > 2 * m) n--, k--;
		else m--, k--;
	}

	printf("%d", (n > m * 2) ? m : n / 2);

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