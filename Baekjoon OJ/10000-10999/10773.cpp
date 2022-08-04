#include <iostream>
using namespace std;

const int MAX = 100000;

int k;
int top = 0, stack[MAX];

int main() {
	scanf("%d", &k);

	for (int i = 0; i < k; i++) {
		int sam;
		scanf("%d", &sam);

		if (sam == 0) {
			if (top != 0) top--;
		}
		else {
			if (top != MAX) {
				stack[top] = sam;
				top++;
			}
		}
	}

	int ans = 0;
	for (int i = 0; i < top; i++)
		ans += stack[i];
	printf("%d", ans);

	return 0;
}
/*
���� �ع�		: 
���� ���		: 
������ ������	: 
���� ����		: 1. 
				  2. 
*/