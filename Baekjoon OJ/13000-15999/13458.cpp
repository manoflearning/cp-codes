#include <iostream>
using namespace std;

int test[1000000];

int main() {
	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		scanf("%d", &test[i]);

	int b, c;
	scanf("%d %d", &b, &c);

	long long ans = n;
	for (int i = 0; i < n; i++) {
		if (test[i] <= b) continue;

		if ((test[i] - b) % c == 0) ans += (test[i] - b) / c;
		else ans += (test[i] - b) / c + 1;
	}

	printf("%lld", ans);

	return 0;
}
/*
���� �ع�		: 
���� ���		: 
������ ������		: 
���� ����		: 1. 
				  2. 
*/
//////////////////////////////////////////////////////////////////////