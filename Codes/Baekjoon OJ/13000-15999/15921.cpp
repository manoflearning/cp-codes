#include <iostream>
using namespace std;

int main() {
	int n;
	scanf("%d", &n);

	int sum = 0;
	for (int i = 0; i < n; i++) {
		int sam;
		scanf("%d", &sam);

		sum += sam;
	}

	if (sum == 0) printf("divide by zero");
	else printf("1.00");

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