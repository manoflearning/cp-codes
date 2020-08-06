#include <iostream>
#include <algorithm>
using namespace std;

int n;
int fence[20000];

int find_max(int left, int right);

int main() {
	int t;
	scanf("%d", &t);

	for (int test = 0; test < t; test++) {
		scanf("%d", &n);

		for (int i = 0; i < n; i++)
			scanf("%d", &fence[i]);

		printf("%d\n", find_max(0, n - 1));
	}

	return 0;
}

int find_max(int left, int right) {
	//base case
	if (left == right) return fence[left];

	int flag = (left + right) / 2;
	
	int ans = max(find_max(left, flag), find_max(flag + 1, right));

	int m1 = flag, m2 = flag + 1;
	int height = min(fence[m1], fence[m2]);
	ans = max(ans, (m2 - m1 + 1) * height);
	while (left < m1 || m2 < right) {
		if (m2 < right && (m1 == left || fence[m1 - 1] < fence[m2 + 1])) {
			m2++;
			height = min(height, fence[m2]);
		}
		else {
			m1--;
			height = min(height, fence[m1]);
		}
		
		ans = max(ans, (m2 - m1 + 1) * height);
	}

	return ans;
}
/*
문제 해법		: 분할정복. 중앙을 기준으로 왼쪽에 위치하는 직사각형, 오른쪽에 위치하는 직사각형, 중앙을 걸치는 직사각형으로 분류.
접근 방식		: 
결정적 깨달음		: 
오답 원인		: 1. 
				  2. 
*/
//////////////////////////////////////////////////////////////////////
