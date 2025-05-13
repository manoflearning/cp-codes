#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 1010101;
const int MOD = 1e9 + 7;

ll dp[N][3][2];

void bottomup() {
    // base case
    dp[1][0][0] = 1;
    dp[1][0][1] = 0;
    dp[1][1][0] = 1;
    dp[1][1][1] = 0;
    dp[1][2][0] = 1;
    dp[1][2][1] = 0;

    // inductive step
    for (int i = 2; i < N; i++) {
        dp[i][0][0] = dp[i - 1][0][0] + dp[i - 1][1][0] + dp[i - 1][1][1]+ dp[i - 1][2][0] + dp[i - 1][2][1];
        dp[i][0][0] %= MOD;

        dp[i][1][0] = dp[i - 1][1][0] + dp[i - 1][2][1];
        dp[i][1][0] %= MOD;

        dp[i][1][1] = dp[i - 1][0][0] + dp[i - 1][1][1];
        dp[i][1][1] %= MOD;

        dp[i][2][0] = dp[i - 1][2][0] + dp[i - 1][1][1];
        dp[i][2][0] %= MOD;

        dp[i][2][1] = dp[i - 1][0][0] + dp[i - 1][2][1];
        dp[i][2][1] %= MOD;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    bottomup();

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        ll ans = 0;
        ans += dp[n][0][0];
        ans += dp[n][1][1];
        ans += dp[n][2][1];
        ans %= MOD;

        cout << ans << '\n';
    }
}
