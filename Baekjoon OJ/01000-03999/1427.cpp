#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

char arr[11];

int main() {
	scanf("%s", arr);

	int flag = strlen(arr);

	for (int i = flag - 1; i > 0; i--) {
		for (int l = 0; l < i; l++) {
			if (arr[l] < arr[l + 1]) {
				int tmp = arr[l];
				arr[l] = arr[l + 1];
				arr[l + 1] = tmp;
			}
		}
	}

	printf("%s", arr);

	return 0;
}

/*
���� �ع�		: ���� ����
���� ���		:
������ ������	:
���� ����		: 1. 
				  2.
*/