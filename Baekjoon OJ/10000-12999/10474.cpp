#include <iostream>
using namespace std;

int main() {
	while (true) {
		long long a, b;
		scanf("%lld %lld", &a, &b);

		if (a == 0 && b == 0) break;

		printf("%lld %lld / %lld\n", a / b, a % b, b);
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