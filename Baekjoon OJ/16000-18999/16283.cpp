#include <iostream>

int a, b, n, w;

int main() {
	scanf("%d %d %d %d", &a, &b, &n, &w);

	if (a == b && n > 2) {
		printf("-1");
		return 0;
	}

	bool flag = false;
	for (int i = 1; i < n; i++) {
		if (a * i + b * (n - i) == w) {
			printf("%d %d", i, n - i);
			flag = true;
			break;
		}
	}

	if (!flag) printf("-1");

	return 0;
}

/*
���� �ع�		: ����
���� ���		:
������ ������	:
���� ����		: 1. 
				  2.
*/