#include <iostream>
#include <algorithm>
using namespace std;

int n;
int arr[8001];

int sum;

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int flag;
		scanf("%d", &flag);

		sum += flag;
		arr[flag + 4000]++;
	}
	//1
	printf("%.0lf\n", (double)sum / n);
	//2
	int count = 0;
	for (int i = 0; ; i++) {
		count += arr[i];
		if (count >= n / 2 + 1) {
			printf("%d\n", i - 4000);
			break;
		}
	}
	//3
	int value = -1;
	for (int i = 0; i <= 8000; i++)
		value = max(value, arr[i]);
	int check = 0;
	for (int i = 0; i <= 8000; i++) {
		if (arr[i] == value) check++;
		if (check == 2) {
			printf("%d\n", i - 4000);
			break;
		}
	}
	if (check == 1) {
		for (int i = 0; i <= 8000; i++) {
			if (arr[i] == value) {
				printf("%d\n", i - 4000);
				break;
			}
		}
	}
	//4
	int min, max;
	for (int i = 0; ; i++) {
		if (arr[i] != 0) {
			min = i;
			break;
		}
	}
	for (int i = 8000; ; i--) {
		if (arr[i] != 0) {
			max = i;
			break;
		}
	}
	printf("%d\n", max - min);

	return 0;
}

/*
문제 해법		: 카운팅 정렬을 활용
접근 방식		:
결정적 깨달음	:
오답 원인		: 1. 
				  2.
*/
