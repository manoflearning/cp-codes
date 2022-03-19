#include <bits/stdc++.h>
using namespace std;

const int MAXD = 17;

//int dp[505][505], a[505][505];

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	/*int n = 3, m = 3;
	for (int i = 1; i <= n; i++) {
		for (int l = 1; l <= m; l++) {
			cin >> a[i][l];
		}
	}
	dp[0][1] = a[1][1];
	for (int i = 1; i <= n; i++) {
		for (int l = 1; l <= m; l++) {
			dp[i][l] = max(dp[i - 1][l] & a[i][l], dp[i][l - 1] & a[i][l]);
		}
	}
	cout << dp[n][m];*/

	int K, MAX = 1; 
	cin >> K;

	for (int i = 0; i < MAXD; i++) {
		if ((1 << i) & K) {
			MAX = (1 << (i + 1));
		}
	}

	cout << "3 3\n";
	cout << K + MAX << ' ' << K << ' ' << 0 << '\n';
	cout << MAX << ' ' << K << ' ' << 0 << '\n';
	cout << MAX << ' ' << K + MAX << ' ' << K << '\n';

	return 0;
}