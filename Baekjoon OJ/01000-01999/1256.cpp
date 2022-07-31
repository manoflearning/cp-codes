#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

ll n, m, k;
ll dp[201][201]; //dp[a][b]는 a 길이의, 'z'의 개수가 b개인 문자열의 개수

void print(int N, int M, int len, int k);

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> m >> k;
	
	dp[1][0] = dp[1][1] = 1;
	for (int i = 2; i <= 200; i++) {
		dp[i][0] = 1;
		for (int l = 1; l <= i; l++) {
			dp[i][l] = min((ll)1e9 + 1, dp[i - 1][l - 1] + dp[i - 1][l]);
		}
	}

	if (k > dp[n + m][m]) cout << -1;
	else print(n, m, n + m, k);

	return 0;
}

void print(int N, int M, int len, int k) {
	if (len <= 0) return;

	if (N == 0) {
		cout << 'z';
		print(N, M - 1, len - 1, k - dp[len - 1][M]);
	}
	else if (M == 0) {
		cout << 'a';
		print(N - 1, M, len - 1, k);
	}
	else if (dp[len - 1][M] >= k) {
		cout << 'a';
		print(N - 1, M, len - 1, k);
	}
	else {
		cout << 'z';
		print(N, M - 1, len - 1, k - dp[len - 1][M]);
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: 동적계획법
접근 방식		:
결정적 깨달음		:
오답 원인		: 1.
				  2.
*/////////////////////////////////////////////////////////////////////