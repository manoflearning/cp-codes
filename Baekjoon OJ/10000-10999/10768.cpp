#include <iostream>
using namespace std;

int main() {
	int month, day;
	scanf("%d %d", &month, &day);

	if (month == 2) {
		if (day == 18) printf("Special");
		else if (day < 18) printf("Before");
		else printf("After");
	}
	else if (month > 2) printf("After");
	else printf("Before");

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