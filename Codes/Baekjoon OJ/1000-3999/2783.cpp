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
문제 해법		: 
접근 방식		: 
결정적 깨달음		: 
오답 원인		: 1. 
				  2. 
*/
//////////////////////////////////////////////////////////////////////