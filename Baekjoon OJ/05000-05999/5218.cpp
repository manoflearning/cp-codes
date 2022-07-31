#include <iostream>
#include <cstring>
using namespace std;

int main() {
	int t;
	scanf("%d", &t);

	for (int test = 0; test < t; test++) {
		char word1[21], word2[21];
		scanf("%s %s", word1, word2);

		int len = strlen(word1);

		printf("Distances: ");
		for (int i = 0; i < len; i++) {
			if (word2[i] >= word1[i]) printf("%d ", word2[i] - word1[i]);
			else printf("%d ", word2[i] + 26 - word1[i]);
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