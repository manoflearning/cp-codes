#include <iostream>
#include <vector>
using namespace std;

vector<bool> card(1000, true);

int main() {
	int n;
	scanf("%d", &n);

	int flag = 0;
	while (flag < n) {
		static int count = 0;

		for (int i = 1; i <= n; i++) {
			if (card[i]) {
				count++;

				if (count % 2 == 1) {
					printf("%d ", i);

					card[i] = false;
					flag++;
				}
			}
		}
	}

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