#include <iostream>
#include <cstring>
using namespace std;

int main() {
	while (1) {
		char name[501];
		fgets(name, sizeof(name), stdin);
		
		if (strcmp(name, "END\n") == 0) break;

		for (int i = strlen(name) - 2; i >= 0; i--) {
			printf("%c", name[i]);
		}
		printf("\n");
	}

	return 0;
}

/*
���� �ع�		: ���ڿ� ó��
���� ���		:
������ ������	:
���� ����		: 1. 
				  2.
*/