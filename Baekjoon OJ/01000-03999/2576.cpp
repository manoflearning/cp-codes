#include <iostream>
using namespace std;

int main() {
	bool check = false;
	int sum = 0, min = 100;
	for (int i = 0; i < 7; i++) {
		int sam;
		scanf("%d", &sam);

		if (sam % 2 == 1) {
			check = true;

			sum += sam;
			if (min > sam) min = sam;
		}
	}

	if (check) printf("%d\n%d", sum, min);
	else printf("-1");

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