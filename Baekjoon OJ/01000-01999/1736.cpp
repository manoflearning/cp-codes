#include <bits/stdc++.h>
using namespace std;

int n, m;
int a[111][111], dp[111][111];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    int ans = 0;
    for (int i = 1; i <= m; i++) {
        dp[1][i] = a[1][i];
        ans = max(ans, dp[1][i]);
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = a[i][j];
            for (int k = j + 1; k <= m; k++) 
                dp[i][j] = max(dp[i][j], a[i][j] + dp[i - 1][k]);

            dp[i][j] = max(dp[i][j], dp[i - 1][j]);

            ans = max(ans, dp[i][j]);
        }
    }

    cout << ans;
}