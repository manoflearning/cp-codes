#include <iostream>
using namespace std;

int main() {
	int t;
	scanf("%d", &t);

	for (int test = 0; test < t; test++) {
		int n;
		scanf("%d", &n);

		int q = 0, d = 0, ni = 0, p = 0;

		while (n >= 25) n -= 25, q++;
		while (n >= 10) n -= 10, d++;
		while (n >= 5) n -= 5, ni++;
		while (n >= 1) n--, p++;

		printf("%d %d %d %d\n", q, d, ni, p);
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