#include <iostream>
using namespace std;

int main() {
	int flag = 0;
	for (int i = 0; i < 4; i++) {
		int sam;
		scanf("%d", &sam);

		flag += sam;
	}

	printf("%d\n%d", flag / 60, flag % 60);

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