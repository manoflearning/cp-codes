#include <iostream>
using namespace std;

int main() {
	long long int a, b, c, d;

	scanf("%lld %lld %lld %lld", &a, &b, &c, &d);

	int flag;
	
	for (flag = 1; flag <= b; flag *= 10);
	a *= flag;

	for (flag = 1; flag <= d; flag *= 10);
	c *= flag;

	printf("%lld", a + b + c + d);

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