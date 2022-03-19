#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

string A, B;
int dp[1005][1005]; //dp[i][l]은 A[0...i]와 B[0...l]의 최장 부분 공통 수열의 길이

int f(int a, int b);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> A >> B;

	memset(dp, -1, sizeof(dp));
	cout << f(A.size() - 1, B.size() - 1);

	return 0;
}

int f(int a, int b) {
	if (a == -1 || b == -1) return 0;
	int& ret = dp[a][b];
	if (ret != -1) return ret;

	if (A[a] == B[b]) ret = f(a - 1, b - 1) + 1;
	else ret = max(f(a - 1, b), f(a, b - 1));

	return ret;
}