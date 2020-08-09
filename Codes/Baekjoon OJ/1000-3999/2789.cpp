#include <iostream>
#include <cstring>
using namespace std;

char word[101];
char checker[9] = { 'C', 'A', 'M', 'B', 'R', 'I', 'D', 'G', 'E' };

int main() {
	scanf("%s", word);

	int len = strlen(word);

	for (int i = 0; i < len; i++) {
		for (int l = 0; l < 9; l++) {
			if (word[i] == checker[l]) break;

			if (l == 8) printf("%c", word[i]);
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
////////////////////////////////////////////////////////////////////////////////