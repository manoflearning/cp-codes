#include <iostream>
#include <cmath>
using namespace std;

int Rev(int num);

int main() {
	int x, y;
	scanf("%d %d", &x, &y);

	x = Rev(x), y = Rev(y);
	int ans = Rev(x + y);

	printf("%d", ans);

	return 0;
}

int Rev(int num) {
	int flag;
	for (flag = 0; pow(10, flag) <= num; flag++);
	flag--;

	int sum = 0;

	for (int i = 0; i <= flag; i++)
		sum += num % (int)pow(10, i + 1) / (int)pow(10, i) * pow(10, flag - i);
		
	return sum;
}
/*
���� �ع�		: 
���� ���		:
������ ������	:
���� ����		: 1. pow�� double�� ��ȯ���� ���� �Լ�! ������ �Ҷ� ����!
				  2.
*/
///////////////////////////////////////////////////////////////////////