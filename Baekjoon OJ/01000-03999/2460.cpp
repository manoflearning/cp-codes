#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int max_peo = -1;
	int sum = 0;
	for (int i = 0; i < 10; i++) {
		int a, b;
		scanf("%d %d", &a, &b);

		sum -= a;
		sum += b;

		max_peo = max(max_peo, sum);
	}

	printf("%d", max_peo);

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