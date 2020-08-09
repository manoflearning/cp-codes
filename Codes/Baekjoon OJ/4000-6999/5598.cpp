#include <iostream>
#include <cstring>
using namespace std;

int main() {
	char word[1001];
	scanf("%s", word);

	int len = strlen(word);
	for (int i = 0; i < len; i++) {
		if (word[i] - 3 < 'A') printf("%c", word[i] + 23);
		else printf("%c", word[i] - 3);
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