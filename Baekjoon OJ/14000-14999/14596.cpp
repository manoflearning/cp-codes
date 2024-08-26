#include <bits/stdc++.h>
using namespace std;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> a(n, vector<int>(m));
    vector<vector<int>> b(n, vector<int>(m));
    for (auto& i : a) for (auto& j : i) cin >> j;
    for (auto& i : b) for (auto& j : i) cin >> j;
    
    // base case
    vector<vector<int>> dp(n, vector<int>(m));

    for (int x = 0; x < m; x++) {
        dp[0][x] = (a[0][x] - b[0][x]) * (a[0][x] - b[0][x]);
    }

    // inductive step
    for (int y = 1; y < n; y++) {
        for (int x = 0; x < m; x++) {
            dp[y][x] = 1e9;
            
            if (0 <= x - 1) dp[y][x] = min(dp[y][x], dp[y - 1][x - 1]);
            dp[y][x] = min(dp[y][x], dp[y - 1][x]);
            if (x + 1 < m) dp[y][x] = min(dp[y][x], dp[y - 1][x + 1]);

            dp[y][x] += (a[y][x] - b[y][x]) * (a[y][x] - b[y][x]);
        }
    }

    int ans = 1e9;
    for (int x = 0; x < m; x++) {
        ans = min(ans, dp[n - 1][x]);
    }
    cout << ans;
}