#include <iostream>
#include <cstring>
using namespace std;

int main() {
	int t;
	scanf("%d", &t);

	for (int test = 0; test < t; test++) {
		int wrong;
		char word[81];

		scanf("%d %s", &wrong, word);

		int len = strlen(word);
		for (int i = 0; i < len; i++) {
			if (i == wrong - 1) continue;

			printf("%c", word[i]);
		}
		printf("\n");
	}

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