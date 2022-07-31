#include <iostream>
using namespace std;

int main() {
	int n;
	scanf("%d", &n);

	for (int i = 1; ; i++) {
		if (1 + i + i * i == n) {
			printf("%d", i);
			break;
		}
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