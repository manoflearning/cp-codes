#include <iostream>
#include <algorithm>
using namespace std;

int arr[(int)1e5];

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	int n, s; 
	cin >> n >> s;

	for (int i = 0; i < n; i++)
		cin >> arr[i];

	int L = 0, sum = 0, min_len = 1e5 + 1;
	for (int i = 0; i < n; i++) {
		sum += arr[i];
		while (sum >= s && L <= i) {
			min_len = min(min_len, i - L + 1);
			sum -= arr[L];
			L++;
		}
	}

	if (min_len == 1e5 + 1) cout << 0;
	else cout << min_len;

	return 0;
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 투포인터
결정적 깨달음		: 
시간복잡도		: O(n)
오답 원인		: 1. "합이 s인"이 아니라 "합이 s 이상인"이었음. 문제를 잘못 읽음. 
				  2. 길이가 1인 경우를 체크하지 못함.
				  3. sum == s인 경우를 체크하지 못함.
*/////////////////////////////////////////////////////////////////////