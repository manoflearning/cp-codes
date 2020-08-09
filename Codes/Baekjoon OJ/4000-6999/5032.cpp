#include <iostream>
using namespace std;

int main() {
	int e, f, c;
	scanf("%d %d %d", &e, &f, &c);

	int empty = e + f;
	int ans = 0;
	while (empty >= c) {
		int flag = empty / c;

		empty %= c;
		empty += flag;
		ans += flag;
	}

	printf("%d", ans);

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