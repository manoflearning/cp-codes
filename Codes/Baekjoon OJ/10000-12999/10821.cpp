#include <iostream>
#include <cstring>
using namespace std;

char S[101];

int main() {
	scanf("%s", S);

	int len = strlen(S);

	int sum = 1;
	for (int i = 0; i < len; i++)
		if (S[i] == ',') sum++;

	printf("%d", sum);

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