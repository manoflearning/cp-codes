#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int MOD = 1'000'000'007;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n, a;
    cin >> n >> a;

    if (10 <= a) {
        cout << 0 << '\n';
        exit(0);
    }
    if (n == 1) {
        cout << (a == 1 ? 9 : 0) << '\n';
        exit(0);
    }
    
    vector<vector<vector<vector<ll>>>> dp(
        a + 1, vector<vector<vector<ll>>>(
            10, vector<vector<ll>>(10, vector<ll>(2))
        )
    );

    // base case
    for (int i = 1; i <= 9; i++) {
        for (int j = i; j <= 9; j++) {
            dp[1][i][j][1] = 1;
        }
    }

    // inductive step
    for (int t = 2; t < n; t++) {
        auto tmp = dp;
        dp.assign(
            a + 1, vector<vector<vector<ll>>>(
                10, vector<vector<ll>>(10, vector<ll>(2, 0))
            )
        );

        for (int cnt = 1; cnt <= a; cnt++) {
            for (int i = 1; i <= 9; i++) {
                for (int j = i; j <= 9; j++) {
                    for (int k = j; k <= 9; k++) {
                        for (int b = 0; b < 2; b++) {
                            if (2 * j == i + k || b == 0) {
                                dp[cnt][j][k][1] += tmp[cnt][i][j][b];
                                dp[cnt][j][k][1] %= MOD;
                            } else if (cnt < a) {
                                dp[cnt + 1][j][k][0] += tmp[cnt][i][j][b];
                                dp[cnt + 1][j][k][0] %= MOD;
                            }
                        }
                        
                    }
                }
            }
        }
    }

    ll ans = 0;
    for (int i = 1; i <= 9; i++) {
        for (int j = i; j <= 9; j++) {
            ans = (ans + dp[a][i][j][0] + dp[a][i][j][1]) % MOD;
        }
    }
    cout << ans << '\n';
}
