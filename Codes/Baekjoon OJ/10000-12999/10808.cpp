#include <iostream>
#include <cstring>
using namespace std;

int main() {
	int ans[26] = { 0, };

	char word[101];
	scanf("%s", word);

	int len = strlen(word);
	for (int i = 0; i < len; i++)
		ans[word[i] - 'a']++;

	for (int i = 0; i < 26; i++)
		printf("%d ", ans[i]);

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