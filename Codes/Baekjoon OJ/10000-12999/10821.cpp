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
���� �ع�		: 
���� ���		: 
������ ������		: 
���� ����		: 1. 
				  2. 
*/
//////////////////////////////////////////////////////////////////////