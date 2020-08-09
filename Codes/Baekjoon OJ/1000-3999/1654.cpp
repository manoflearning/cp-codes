#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int k, n;
vector<int> len;

int bsearch(long long int left, long long int right);
bool fact_check(long long int flag);

int main() {
	//input
	scanf("%d %d", &k, &n);
	len.resize(k);
	for (int i = 0; i < k; i++)
		scanf("%d", &len[i]);
	//output
	int ans = bsearch(0, INT_MAX);
	printf("%d", ans);

	return 0;
}

int bsearch(long long int left, long long int right) {
	int flag = (left + right) / 2;

	if (!fact_check(flag)) return bsearch(left, flag - 1);
	else {
		if (!fact_check(flag + 1)) return flag;
		else return bsearch(flag + 1, right);
	}
}
bool fact_check(long long int flag) {
	long long int sum = 0;
	for (int i = 0; i < k; i++) {
		sum += len[i] / flag;
	}

	if (sum >= n) return true;
	else return false;
}

/*
문제 해법		: 이분 탐색
접근 방식		:
결정적 깨달음	:
오답 원인		: 1. 
				  2.
*/
