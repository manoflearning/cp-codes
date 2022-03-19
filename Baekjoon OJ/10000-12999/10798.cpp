#include <iostream>
using namespace std;

char arr[5][16];

int main() {
	for (int i = 0; i < 5; i++) {
		scanf("%s", arr[i]);
	}

	for (int i = 0; i < 15; i++) {
		for (int l = 0; l < 5; l++) {
			if (arr[l][i] == 0 || arr[l][i] == '\0') continue;

			printf("%c", arr[l][i]);
		}
	}

	return 0;
}
/*
문제 해법		: 
접근 방식		:
결정적 깨달음	: 
오답 원인		: 1. 
				  2.
*/
//////////////////////////////////////////////////////////////////////