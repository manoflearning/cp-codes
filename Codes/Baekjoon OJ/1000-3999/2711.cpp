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
문제 해법		: 
접근 방식		: 
결정적 깨달음		: 
오답 원인		: 1. 
				  2. 
*/
//////////////////////////////////////////////////////////////////////