#include <iostream>
#include <cstring>
using namespace std;

char name[101];

int main() {
	scanf("%s", name);

	for (int i = 0; i < strlen(name); i++) {
		if (65 <= name[i] && name[i] <= 90)
			printf("%c", name[i]);
	}

	return 0;
}

/*
문제 해법		: 문자열 처리
접근 방식		:
결정적 깨달음	:
오답 원인		: 1. 
				  2.
*/