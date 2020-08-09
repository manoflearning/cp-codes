#include <iostream>
using namespace std;

int num[1000000];

int main() {
	int n, p;
	scanf("%d %d", &n, &p);

	num[0] = n;

	bool escape = true;
	for (int i = 1; escape; i++) {
		num[i] = num[i - 1] * n % p;
		
		for (int l = 0; l < i; l++)
			if (num[i] == num[l]) {
				printf("%d", i - l);
				
				escape = false;
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