#include <iostream>
using namespace std;

int main() {
	int a = 0, b = 0;

	for (int i = 0; i < 4; i++) {
		int sam;
		scanf("%d", &sam);
		a += sam;
	}
	for (int i = 0; i < 4; i++) {
		int sam;
		scanf("%d", &sam);
		b += sam;
	}

	printf("%d", a >= b ? a : b);

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