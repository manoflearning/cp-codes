#include <iostream>
using namespace std;

int main() {
	int sum;
	scanf("%d", &sum);

	for (int i = 0; i < 9; i++) {
		int sam;
		scanf("%d", &sam);

		sum -= sam;
	}

	printf("%d", sum);

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