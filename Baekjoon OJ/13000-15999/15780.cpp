#include <iostream>
using namespace std;

int main() {
	int n, k;
	scanf("%d %d", &n, &k);

	int sum_k = 0;
	for (int i = 0; i < k; i++) {
		int sam;
		scanf("%d", &sam);

		sum_k += (sam % 2 == 1) ? sam / 2 + 1 : sam / 2;
	}

	if (sum_k >= n) printf("YES");
	else printf("NO");

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