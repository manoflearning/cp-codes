#include <iostream>
using namespace std;

int main() {
	int n[3] = { 1, 2, 3 };

	int m;
	scanf("%d", &m);

	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);

		for (int l = 0; l < 3; l++) {
			if (n[l] == a) n[l] = b;
			else if (n[l] == b) n[l] = a;
		}
	}

	printf("%d", n[0]);

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