#include <iostream>
#include <cstring>
using namespace std;

char word[101];

int main() {
	scanf("%s", word);

	bool check = true;
	for (int i = 0; i < strlen(word) / 2; i++) {
		if (word[i] != word[strlen(word) - 1 - i]) {
			check = false;
			break;
		}
	}

	if (check) printf("1");
	else printf("0");

	return 0;
}
/*
���� �ع�		: 
���� ���		:
������ ������	: 
���� ����		: 1. 
				  2.
*/
//////////////////////////////////////////////////////////////////////