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
���� �ع�		: ����
���� ���		: 
������ ������	: 
���� ����		: 1. 
				  2. 
*/
//////////////////////////////////////////////////////////////////////