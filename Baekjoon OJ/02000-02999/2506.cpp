#include <iostream>
using namespace std;

int problem[100];

int main() {
	int n;
	scanf("%d", &n);

	int count = 1, ans = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &problem[i]);

		if (problem[i] == 1) {
			ans += count;
			count++;
		}
		else count = 1;
	}

	printf("%d", ans);

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