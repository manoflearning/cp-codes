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
���� �ع�		: 
���� ���		:
������ ������		:
���� ����		: 1. 
				  2.
*/
//////////////////////////////////////////////////////////////////////