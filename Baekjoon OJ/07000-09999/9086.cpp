#include <iostream>
#include <cstring>
using namespace std;

int main() {
	int t;
	scanf("%d", &t);

	for (int i = 0; i < t; i++) {
		char arr[101];
		scanf("%s", arr);

		printf("%c%c\n", arr[0], arr[strlen(arr) - 1]);
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