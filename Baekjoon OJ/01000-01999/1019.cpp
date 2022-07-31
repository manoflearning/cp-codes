#include <iostream>
#include <cmath>
using namespace std;

int cnt[10];

void count_1to9(int num, int flag);
long long int sum_count(int num);

int main() {
	int n;
	scanf("%d", &n);

	int flag;
	for (flag = 0; pow(10, flag) <= n; flag++);

	count_1to9(n, --flag);

	long long int cnt0 = sum_count(n);
	for (int i = 1; i < 10; i++)
		cnt0 -= cnt[i];
	cnt[0] = cnt0;

	for (int i = 0; i < 10; i++)
		printf("%d ", cnt[i]);

	return 0;
}

void count_1to9(int num, int flag) {
	//base case
	if (flag == 0) {
		for (int i = 1; i <= num; i++)
			cnt[i]++;
		return;
	}
	//
	int key = pow(10, flag);
	int n = num / key;

	if (n == 0) count_1to9(num, flag - 1);
	else {
		for (int i = 1; i < n; i++)
			cnt[i] += key;
		cnt[n] += num - n * key + 1;

		int sam = n * key / 10 * flag;
		for (int i = 1; i < 10; i++)
			cnt[i] += sam;

		count_1to9(num - n * key, flag - 1);
	}
}

long long int sum_count(int num) {
	//base case
	if (num <= 9) return num;
	//
	int flag;
	for (flag = 0; pow(10, flag) <= num; flag++);
	flag--;

	long long int sum = sum_count(pow(10, flag) - 1) + ((long long int)flag + 1) * (num - (pow(10, flag) - 1));

	return sum;
}
/*
문제 해법		: 1 ~ 99...999까지일 때 1부터 9까지의 등장횟수를 구하는 식을 귀납적으로 유도함. 0 ~ 99...999를 기준으로 수를 분할하고, 재귀호출을 사용해 n까지의 수 중 1 ~ 9 까지의 등장 횟수를 구함. 전체 수의 등장 횟수를 구하는 함수를 따로 만든 후, 전체 등장횟수에서 1~9까지의 등장 횟수를 뺌 -> 0의 등장 횟수 얻음.
접근 방식		:
결정적 깨달음	:
오답 원인		: 1. 
				  2.
*/
//////////////////////////////////////////////////////////////////////
//O(n)인 프로그램, 제출용 X, 본코드 짜기 위한 도움용 코드 O
/*
#include <iostream>
using namespace std;

long long int sum_count(int num);

int main() {
	while (true) {
		int n;
		scanf("%d", &n);

		int cnt[10];
		for (int i = 0; i < 10; i++)
			cnt[i] = 0;

		for (int i = 1; i <= n; i++) {
			for (int l = 1; l <= i; l *= 10) {
				cnt[i % (l * 10) / l]++;
			}
		}

		int sum = 0;
		for (int i = 0; i < 10; i++) {
			printf("%d ", cnt[i]);
			sum += cnt[i];
		}
		printf("\n%d %lld\n", sum, sum_count(n));
	}

	return 0;
}

long long int sum_count(int num) {
	//base case
	if (num <= 9) return num;
	//
	int flag;
	for (flag = 0; pow(10, flag) <= num; flag++);
	flag--;

	int sum = sum_count(pow(10, flag) - 1) + (flag + 1) * (num - (pow(10, flag) - 1));

	return sum;
}
*/