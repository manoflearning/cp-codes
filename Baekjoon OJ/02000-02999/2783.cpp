#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	double x, y;
	scanf("%lf %lf", &x, &y);

	double price = 100001;
	price = min(price, x * (1000 / y));
	
	int t;
	scanf("%d", &t);
	for (int test = 0; test < t; test++) {
		scanf("%lf %lf", &x, &y);

		price = min(price, x * (1000 / y));
	}

	printf("%.3lf", price);

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