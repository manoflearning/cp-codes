#include <iostream>
using namespace std;

int main() {
	int n;
	scanf("%d", &n);

	if (n % 2 != 0) printf("0");
	else if (n / 2 % 2 != 0) printf("1");
	else printf("2");

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