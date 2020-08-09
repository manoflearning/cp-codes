#include <iostream>
using namespace std;

int main() {
	int count[101] = { 0, };
	int sum = 0;

	for (int i = 0; i < 10; i++) {
		int num;
		scanf("%d", &num);

		sum += num;
		count[num / 10]++;
	}

	int flag = 1;
	for (int i = 2; i <= 100; i++)
		if (count[i] > count[flag]) flag = i;

	printf("%d\n%d", sum / 10, flag * 10);

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