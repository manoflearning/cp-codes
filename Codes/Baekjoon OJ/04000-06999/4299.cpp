#include <iostream>
using namespace std;

int main() {
	int a, b;
	scanf("%d %d", &a, &b);

	if (a < b || (a - b) % 2 != 0) printf("-1");
	else printf("%d %d", (a + b) / 2, (a - b) / 2);

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