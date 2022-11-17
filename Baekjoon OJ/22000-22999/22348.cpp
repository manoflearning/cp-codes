#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int a, b;
int dp[2][50505], psum[455][50505];

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
    
    dp[0][0] = 1;
    for (int i = 1; i * (i + 1) / 2 <= 100000; i++) {
        int bit = (i & 1);
        memset(dp[bit], 0, sizeof(dp[bit]));

        for (int j = 0; j <= 50000; j++) {
            if (dp[!bit][j]) {
                dp[bit][j + i] = (dp[bit][j + i] + dp[!bit][j]) % MOD;
                dp[bit][j] = (dp[bit][j] + dp[!bit][j]) % MOD;
            }

            if (j == 0) psum[i][j] = dp[bit][j];
            else psum[i][j] = (dp[bit][j] + psum[i][j - 1]) % MOD;
        }
    }

	int tc; cin >> tc;
    while (tc--) {
        cin >> a >> b;

        int ans = 0;

        for (int i = 1; i * (i + 1) / 2 <= 100000; i++) {
            int sum = i * (i + 1) / 2;

            if (sum > a + b) break;
            ans = (ans + psum[i][a] - (sum - b - 1 >= 0 ? psum[i][sum - b - 1] : 0)) % MOD;
        }

        ans = (ans + MOD) % MOD;
        cout << ans << '\n';
    }

	return 0;
}