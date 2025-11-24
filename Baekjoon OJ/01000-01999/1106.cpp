#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 1e9 + 7;
constexpr int C = 1010;
constexpr int N = 22;

int dp[N][C + 100];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < C + 100; j++) dp[i][j] = INF;

    // base case
    dp[0][0] = 0;

    int c, n;
    cin >> c >> n;

    // inductive step
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;

        for (int j = 0; j <= c + 100; j++) {
            for (int k = j; k >= 0; k -= y) {
                dp[i][j] = min(dp[i][j], dp[i - 1][k] + (j - k) / y * x);
            }
        }
    }

    int ans = INF;
    for (int i = c; i <= c + 100; i++)
        ans = min(ans, dp[n][i]);
    cout << ans;
}