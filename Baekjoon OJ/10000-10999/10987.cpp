#include <iostream>
#include <cstring>
using namespace std;

int main() {
	char word[101];
	scanf("%s", word);

	int ans = 0;
	int len = strlen(word);
	for (int i = 0; i < len; i++) {
		if (word[i] == 'a' || word[i] == 'e' || word[i] == 'i' || word[i] == 'o' || word[i] == 'u')
			ans++;
	}

	printf("%d", ans);

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