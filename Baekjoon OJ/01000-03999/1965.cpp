#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> box;

vector<int> dp;

int main() {
	scanf("%d", &n);

	box.resize(n);
	dp.resize(n);

	for (int i = 0; i < n; i++)
		scanf("%d", &box[i]);

	dp[0] = 1;

	int ans = dp[0];

	for (int i = 1; i < n; i++) {
		int dp_max = 0;
		for (int l = 0; l < i; l++) {
			if (box[l] < box[i]) dp_max = max(dp_max, dp[l]);
		}

		dp[i] = dp_max + 1;

		ans = max(ans, dp[i]);
	}

	printf("%d", ans);

	return 0;
}
/*
���� �ع�		: ���� ��ȹ��(bottom up)
���� ���		: 
������ ������	: 
���� ����		: 1. dp_max ������ �ʱⰪ ������ �߸���.
				  2. 
*/
//////////////////////////////////////////////////////////////////////