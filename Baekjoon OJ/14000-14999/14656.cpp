#include <iostream>
using namespace std;

int main() {
	int n;
	scanf("%d", &n);
	
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		int flag;
		scanf("%d", &flag);

		if (flag != i) ans++;
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