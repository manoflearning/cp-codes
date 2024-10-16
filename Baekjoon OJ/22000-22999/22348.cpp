#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1e9 + 7;
const int MXT = 455;

ll dp[MXT][50505], psum[MXT][50505];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    dp[0][0] = 1;
    for (int i = 1; i < MXT; i++) {
        for (int j = 0; j < 50505; j++) {
            if (dp[i - 1][j]) {
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
                if (j + i < 50505) dp[i][j + i] = (dp[i][j + i] + dp[i - 1][j]) % MOD;
            }
        }

        psum[i][0] = dp[i][0];
        for (int j = 1; j < 50505; j++) {
            psum[i][j] = (psum[i][j - 1] + dp[i][j]) % MOD;
        }
    }

    int tc; cin >> tc;
    while (tc--) {
        int x, y;
        cin >> x >> y;

        ll ans = 0;
        for (int i = 1; i * (i + 1) / 2 <= x + y; i++) {
            int idx = i * (i + 1) / 2 - y - 1;
            ll res = psum[i][x] - (0 <= idx && idx < 50505 ? psum[i][idx] : 0);
            ans = (ans + res + MOD) % MOD;
        }
        cout << ans << '\n';
    }
}