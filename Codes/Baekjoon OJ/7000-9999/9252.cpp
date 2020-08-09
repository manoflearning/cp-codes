#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAX = 1000;

string s1, s2;
int dp[MAX + 5][MAX + 5];

int LCS(int n1, int n2);
void trace(int n1, int n2);

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	memset(dp, -1, sizeof(dp));

	cin >> s1 >> s2;

	int ans = LCS(0, 0);

	cout << ans << '\n';

	trace(0, 0);

	return 0;
}

int LCS(int n1, int n2) {
	int& ret = dp[n1][n2];
	//memoization
	if (ret != -1) return ret;
	//base case
	if (n1 == s1.size() || n2 == s2.size()) return ret = 0;
	//
	if (s1[n1] == s2[n2]) ret = LCS(n1 + 1, n2 + 1) + 1;
	else ret = max(LCS(n1 + 1, n2), LCS(n1, n2 + 1));

	return ret;
}

void trace(int n1, int n2) {
	//base case
	if (n1 == s1.size() || n2 == s2.size()) return ;

	if (s1[n1] == s2[n2]) {
		cout << s1[n1];
		trace(n1 + 1, n2 + 1);
	}
	else {
		if (dp[n1 + 1][n2] >= dp[n1][n2 + 1]) trace(n1 + 1, n2);
		else trace(n1, n2 + 1);
	}
}
/*////////////////////////////////////////////////////////////////////
문제 해법		: dp, dp 역추적
결정적 깨달음		: 
시간복잡도		: O(n^2)
오답 원인		: 1. 
				  2.
*/////////////////////////////////////////////////////////////////////