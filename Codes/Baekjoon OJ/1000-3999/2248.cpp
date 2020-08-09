#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

ll N, L, I;
ll dp[32][32], dpL[32][32];

void print(int len, int rem, ll cnt);

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> L >> I;

	dp[0][0] = dpL[0][0] = 1;
	for (int i = 1; i <= 31; i++) {
		dp[i][0] = dpL[i][0] = 1;
		for (int l = 1; l <= i; l++) {
			dp[i][l] = dp[i - 1][l - 1] + dp[i - 1][l];
			dpL[i][l] = dpL[i][l - 1] + dp[i][l];
		}
	}

	print(N, L, I);

	return 0;
}

void print(int len, int rem, ll cnt) {
	if (len <= 0) return;
	
	if (rem == 0) {
		cout << 0;
		print(len - 1, rem, cnt);
	}
	else if (cnt <= dpL[len - 1][min(len - 1, rem)]) {
		cout << 0;
		print(len - 1, min(rem, len - 1), cnt);
	}
	else {
		cout << 1;
		print(len - 1, min(rem - 1, len - 1), cnt - dpL[len - 1][min(len - 1, rem)]);
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 동적계획법
접근 방식		:
결정적 깨달음		:
오답 원인		: 1. dpL[0][0]을 정의하지 않음.
				  2. 오버플로우
*/////////////////////////////////////////////////////////////////////