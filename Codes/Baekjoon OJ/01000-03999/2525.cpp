#include <iostream>
using namespace std;

int main() {
	int a, b;

	scanf("%d %d", &a, &b);

	int c;
	scanf("%d", &c);
	
	b += c % 60;
	if (b >= 60) {
		b %= 60;
		a += 1;
	}
	a += c / 60;
	a %= 24;

	printf("%d %d", a, b);

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