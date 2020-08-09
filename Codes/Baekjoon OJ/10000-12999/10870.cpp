/*
문제 해법		: 단순 재귀호출
접근 방식		:
결정적 깨달음	:
오답 원인		: 1.
				  2.
*/

#include <iostream>
#include <vector>

using namespace std;

int n;
int fibonacci(int n);

int main()
{
	scanf("%d", &n);

	printf("%d", fibonacci(n));

	return 0;
}

int fibonacci(int n)
{
	if (n == 0) return 0;
	if (n == 1) return 1;

	return fibonacci(n - 1) + fibonacci(n - 2);
}