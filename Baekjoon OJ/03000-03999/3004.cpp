#include <iostream>
#include <cstring>
using namespace std;

int main() {
	int n;
	scanf("%d", &n);

	if (n % 2 == 0) printf("%d", (n / 2 + 1) * (n / 2 + 1));
	else printf("%d", (n / 2 + 2) * (n / 2 + 1));

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