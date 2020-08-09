#include <iostream>
#include <algorithm>
using namespace std;

int arr[30001], eaten[3001];

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n, d, k, c;
	cin >> n >> d >> k >> c;

	for (int i = 1; i <= n; i++)
		cin >> arr[i];

	int ans = 0;

	int sum = 1, pre = 1;
	eaten[c]++;
	for (int i = 1; i <= k; i++) {
		if (eaten[arr[i]] == 0) sum++;
		eaten[arr[i]]++;
	}

	ans = max(ans, sum);

	for (int i = k + 1; i <= n; i++) {
		eaten[arr[pre]]--;
		if (eaten[arr[pre]] == 0) sum--;
		pre++;

		if (eaten[arr[i]] == 0) sum++;
		eaten[arr[i]]++;

		ans = max(ans, sum);
	}

	for (int i = 1; i <= k - 1; i++) {
		eaten[arr[pre]]--;
		if (eaten[arr[pre]] == 0) sum--;
		pre++;

		if (eaten[arr[i]] == 0) sum++;
		eaten[arr[i]]++;

		ans = max(ans, sum);
	}
	
	cout << ans;

	return 0;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 슬라이딩 윈도우
결정적 깨달음		: 
시간복잡도		: O(n)
오답 원인		: 1. 배열의 범위를 잘못 설정함
				  2. 
*/////////////////////////////////////////////////////////////////////