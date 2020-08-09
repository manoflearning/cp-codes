#include <iostream>

using namespace std;

int n;
int arr[10001];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int flag;
		scanf("%d", &flag);
		arr[flag]++;
	}

	for (int i = 1; i <= 10000; i++) {
		for (int l = 0; l < arr[i]; l++)
			printf("%d\n", i);
	}

	return 0;
}

/*
문제 해법		: 카운팅 정렬
접근 방식		:
결정적 깨달음	:
오답 원인		: 1. for문 범위 잘못 설정함
				  2.
*/