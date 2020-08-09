#include <iostream>
using namespace std;

int main() {
	int k, n;
	scanf("%d %d", &k, &n);

	int time = 0;

	for (int i = 0; i < n; i++) {
		int s;
		char a;

		scanf("%d %c", &s, &a);

		time += s;

		if (time >= 210) break;

		if (a == 'T') {
			if (k == 8) k = 1;
			else k++;
		}
	}

	printf("%d", k);

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