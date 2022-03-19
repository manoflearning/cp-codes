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
문제 해법		: 
접근 방식		:
결정적 깨달음	: 
오답 원인		: 1. 
				  2.
*/
//////////////////////////////////////////////////////////////////////