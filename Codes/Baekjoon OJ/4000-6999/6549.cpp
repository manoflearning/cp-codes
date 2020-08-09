#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 100000;

int histo[MAX];

long long find_max(int left, int right);

int main() {
	while (true) {
		int n;
		scanf("%d", &n);

		if (n == 0) break;

		for (int i = 0; i < n; i++)
			scanf("%lld", &histo[i]);

		printf("%lld\n", find_max(0, n - 1));
	}

	return 0;
}

long long find_max(int left, int right) {
	//base case
	if (left == right) return histo[left];
	
	int flag = (left + right) / 2;

	int r_left = flag, r_right = flag + 1;
	long long height = min(histo[r_left], histo[r_right]);
	
	long long ret = height * (r_right - r_left + 1);
	
	while (left < r_left || r_right < right) {
		if (r_right < right && (r_left == left || histo[r_left - 1] <= histo[r_right + 1])) {
			r_right++;
			height = min(height, (long long)histo[r_right]);
		}
		else {
			r_left--;
			height = min(height, (long long)histo[r_left]);
		}
		
		ret = max(ret, height * (r_right - r_left + 1));
	}
	
	ret = max(ret, find_max(left, flag));
	ret = max(ret, find_max(flag + 1, right));

	return ret;
}
/*//////////////////////////////////////////////////////////////////////
문제 해법		: 분할 정복
접근 방식		: 
결정적 깨달음		: 
오답 원인		: 1. 
				  2. 
*///////////////////////////////////////////////////////////////////////