#include <iostream>
#include <algorithm>
using namespace std;

int n;
int arr[3];
int dp_min[2][3];
int dp_max[2][3];

int main() {
	scanf("%d", &n);
	
	for (int i = 0; i < 3; i++) {
		scanf("%d", &arr[i]);

		dp_min[0][i] = arr[i];
		dp_max[0][i] = arr[i];
	}
	for (int i = 1; i < n; i++) {
		scanf("%d %d %d", &arr[0], &arr[1], &arr[2]);

		bool flag = (i % 2) ? 1 : 0;
		
		dp_min[flag][0] = arr[0] + min(dp_min[!flag][0], dp_min[!flag][1]);
		dp_min[flag][1] = arr[1] + min(dp_min[!flag][0], min(dp_min[!flag][1], dp_min[!flag][2]));
		dp_min[flag][2] = arr[2] + min(dp_min[!flag][1], dp_min[!flag][2]);

		dp_max[flag][0] = arr[0] + max(dp_max[!flag][0], dp_max[!flag][1]);
		dp_max[flag][1] = arr[1] + max(dp_max[!flag][0], max(dp_max[!flag][1], dp_max[!flag][2]));
		dp_max[flag][2] = arr[2] + max(dp_max[!flag][1], dp_max[!flag][2]);
	}
	
	int ans_flag = (n % 2) ? 0 : 1;
	printf("%d %d", max(dp_max[ans_flag][0], max(dp_max[ans_flag][1], dp_max[ans_flag][2])), min(dp_min[ans_flag][0], min(dp_min[ans_flag][1], dp_min[ans_flag][2])));

	return 0;
}
/*
문제 해법		: 동적계획법. 모든 경우의 수를 메모이제이션하는 것이 아니라, 필요 없는 데이터는 삭제함. bottom up으로 구현하는 것이 좋음.
접근 방식		:
결정적 깨달음	:
오답 원인		: 1. 메모리 제한을 고려하지 않아, 일반적인 동적계획법으로 구현함.
				  2.
*/
///////////////////////////////////////////////////////////////////////