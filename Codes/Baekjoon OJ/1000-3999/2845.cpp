#include <iostream>
using namespace std;

int main() {
	int a, b;
	scanf("%d %d", &a, &b);

	int flag = a * b;

	for (int i = 0; i < 5; i++) {
		int sam;
		scanf("%d", &sam);

		printf("%d\n", sam - flag);
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