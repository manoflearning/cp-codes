#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n, l, r;
ll dp[25][25][25];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    dp[1][1][1] = 1;
    for (int i = 2; i <= 20; i++) {
        for (int j = 1; j <= i - 1; j++) {
            for (int k = 1; k <= i - 1; k++) {
                dp[i][j][k] += (i - 2) * dp[i - 1][j][k];
                dp[i][j + 1][k] += dp[i - 1][j][k];
                dp[i][j][k + 1] += dp[i - 1][j][k];
            }
        }
    }

    int tc; cin >> tc;
    while (tc--) {
        cin >> n >> l >> r;
        cout << dp[n][l][r] << '\n';
    }
}