#include <iostream>
#include <vector>
using namespace std;

long long int small, big;
vector<bool> check;

long long int smallest(long long int checker);

int main() {
	scanf("%lld %lld", &small, &big);

	check.resize(big - small + 1, true);
	
	while (true) {
		static int flag = 2;
		long long int checker = (long long int)flag * flag;

		if (checker > big) break;

		for (long long int i = smallest(checker); i <= big; i += checker) {
			check[i - small] = false;
		}

		flag++;
	}
	
	int ans = 0;
	for (int i = 0; i <= big - small; i++)
		if (check[i]) ans++;

	printf("%d", ans);

	return 0;
}

long long int smallest(long long int checker) {
	long long int ans = small - (small % checker);

	if (ans != small) ans += checker;

	return ans;
}
/*
���� �ع�		: �����佺�׳׽��� ü ����
���� ���		:
������ ������	:
���� ����		: 1.
				  2.
*/
//////////////////////////////////////////////////////////////////////