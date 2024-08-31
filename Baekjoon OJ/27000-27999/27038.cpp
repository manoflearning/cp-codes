#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n, s;
ll dp[252][12121];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin >> n >> s;

    dp[0][0] = 1;
    for (int x = 1; x <= 1000; x++) {
        for (int i = min(n, x) - 1; i >= 0; i--) {
            for (int j = 0; j + x * x < s; j++) {
                dp[i + 1][j + x * x] += dp[i][j];
            }
        }
    }

    ll ans = 0;
    for (int i = 0; i < s; i++) ans += dp[n][i];
    cout << ans;
}
