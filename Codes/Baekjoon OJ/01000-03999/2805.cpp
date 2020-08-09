#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<int> tree;

int binary_flag(int left, int right);

bool fact_check(int flag);

int main() {
	//input
	scanf("%d %d", &n, &m);
	tree.resize(n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &tree[i]);
	}
	//
	sort(tree.begin(), tree.end());
	//output
	int ans = binary_flag(0, 1000000000);
	printf("%d", ans);

	return 0;
}

int binary_flag(int left, int right) {
	int flag = (left + right) / 2;
	
	if (!fact_check(flag)) return binary_flag(left, flag - 1);
	else {
		if (!fact_check(flag + 1)) return flag;
		else return binary_flag(flag + 1, right);
	}
}

bool fact_check(int flag) {
	long long int sum = 0;
	for (int i = n - 1; i >= 0; i--) {
		if (tree[i] >= flag)
			sum += tree[i] - flag;
		else break;
	}

	if (sum >= m) return true;
	else return false;
}

/*
문제 해법		: 이분탐색
접근 방식		:
결정적 깨달음	:
오답 원인		: 1. sum 변수가 int형 범위를 넘어갈 수 있음
				  2.
*/