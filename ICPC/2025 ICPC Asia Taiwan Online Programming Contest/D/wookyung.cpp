#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        string s; cin >> s;

        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, INF));

        for (int i = 0; i + 1 < n; i++) dp[i + 1][i] = 0;
        for (int i = 0; i < n; i++) dp[i][i] = 0;

        for (int len = 2; len <= n; len++) {
            for (int i = 0; ; i++) {
                int j = i + len - 1;
                if (j >= n) break;

                dp[i][j] = min(dp[i][j], dp[i + 1][j] + 1);
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
                dp[i][j] = min(dp[i][j], dp[i + 1][j - 1] + (s[i] != s[j]));
            }
        }

        cout << dp[0][n - 1] << '\n';
    }
}
