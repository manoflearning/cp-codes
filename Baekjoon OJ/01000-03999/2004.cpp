#include <iostream>
#include <algorithm>
using namespace std;

int factor_count(int x, int flag);

int main() {
	int n, m;

	scanf("%d %d", &n, &m);

	int ans1 = factor_count(n, 5) - (factor_count(n - m, 5) + factor_count(m, 5));
	int ans2 = factor_count(n, 2) - (factor_count(n - m, 2) + factor_count(m, 2));
	
	printf("%d", min(ans1, ans2));

	return 0;
}

int factor_count(int x, int flag) {
	int count = 0;
	for (long long int i = flag; i <= x; i *= flag) {
		count += x / i;
	}

	return count;
}

/*
문제 해법		: 수학
접근 방식		:
결정적 깨달음	:
오답 원인		: 1. 오버플로우
				  2.
*/
/* 선형 시간 알고리즘 : 시간 초과
#include <iostream>
using namespace std;

int main() {
	int n, m;
	scanf("%d %d", &n, &m);

	if (m > n / 2) m = n - m;

	int c2_1 = 0, c2_2 = 0;
	for (int i = n - n % 2; i > n - m; i -= 2) {
		int sam = i;
		do {
			sam /= 2;
			c2_1++;
		} while (sam % 2 == 0);
	}
	for (int i = 2; i <= m; i += 2) {
		int sam = i;
		do {
			sam /= 2;
			c2_2++;
		} while (sam % 2 == 0);
	}

	int count = 0;
	for (int i = n - n % 5; i > n - m; i -= 5) {
		int sam = i;
		do {
			if (c2_1 == 0) {
				i = n - m;
				break;
			}
			c2_1--;

			sam /= 5;
			count++;
		} while (sam % 5 == 0);
	}
	for (int i = 5; i <= m; i += 5) {
		int sam = i;
		do {
			if (c2_2 == 0) {
				i = m + 1;
				break;
			}
			c2_2--;

			sam /= 5;
			count--;
		} while (sam % 5 == 0);
	}

	printf("%d", count);

	return 0;
}
*/
/*
문제 해법		: 수학
접근 방식		:
결정적 깨달음	:
오답 원인		: 1.
				  2.
*/
