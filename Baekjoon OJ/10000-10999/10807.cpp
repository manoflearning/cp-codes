#include <iostream>
using namespace std;

int main() {
	int n;
	scanf("%d", &n);

	int num[100];
	for (int i = 0; i < n; i++)
		scanf("%d", &num[i]);

	int v;
	scanf("%d", &v);

	int ans = 0;
	for (int i = 0; i < n; i++) {
		if (num[i] == v) ans++;
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