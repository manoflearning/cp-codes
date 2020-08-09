#include <iostream>
#include <algorithm>
using namespace std;

int a, b;

int main() {
	int t;
	scanf("%d", &t);

	for (int test = 0; test < t; test++) {
		scanf("%d %d", &a, &b);

		if (b > a) swap(a, b);

		int cal = a;

		while (cal % b != 0) cal += a;

		printf("%d\n", cal);
	}
}
/*
문제 해법		: 수학
접근 방식		: 
결정적 깨달음	: 
오답 원인		: 1. 
				  2. 
*/
//////////////////////////////////////////////////////////////////////