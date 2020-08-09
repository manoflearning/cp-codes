#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	double h, w;
	scanf("%lf %lf", &h, &w);

	if (w > h) swap(h, w);

	if (h >= 3 * w) printf("%lf", w);
	else {
		double ans = max(h / 3, w / 2);

		printf("%lf", ans);
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