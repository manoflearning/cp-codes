#include <iostream>
using namespace std;

int main() {
	int a, b;
	scanf("%d %d", &a, &b);

	int flag = a * b;

	for (int i = 0; i < 5; i++) {
		int sam;
		scanf("%d", &sam);

		printf("%d\n", sam - flag);
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