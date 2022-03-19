#include <iostream>
using namespace std;

int main() {
	int n, t;
	scanf("%d %d", &n, &t);

	bool check = true;
	for (int i = 1; i <= n; i++) {
		int sam;
		scanf("%d", &sam);
		
		if (sam <= t) t -= sam;
		else if (check) {
			printf("%d", i - 1);
			check = false;
		}
	}
	if (check) printf("%d", n);

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