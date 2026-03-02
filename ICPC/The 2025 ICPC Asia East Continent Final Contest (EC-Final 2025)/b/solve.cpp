#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int MOD = 998'244'353;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n;
    string s;
    cin >> n >> s;

    assert(sz(s) == 4 * n);

    reverse(all(s));

    vector<vector<vector<ll>>> dp(n + 1, vector<vector<ll>>(n + 1, vector<ll>(n + 1)));

    // base case
    dp[0][0][0] = 1;

    // inductive step
    for (int l = 0; l < 4 * n; l++) {
        vector<vector<vector<ll>>> tmp(n + 1, vector<vector<ll>>(n + 1, vector<ll>(n + 1)));

        const char c = s[l];
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= i; j++) {
                for (int k = 0; k <= j; k++) {
                    if (!dp[i][j][k]) continue;

                    const int puc = k - (l - (i + j + k));

                    if (c == 'p' || c == '?') {
                        if (i < n) {
                            tmp[i + 1][j][k] = (tmp[i + 1][j][k] + dp[i][j][k]) % MOD;
                        }
                    }
                    if (c == 'u' || c == '?') {
                        if (j < i) {
                            tmp[i][j + 1][k] = (tmp[i][j + 1][k] + dp[i][j][k]) % MOD;
                        } else if (puc > 0) {
                            tmp[i][j][k] = (tmp[i][j][k] + dp[i][j][k]) % MOD;
                        }
                    }
                    if (c == 'c' || c == '?') {
                        if (j > k) {
                            tmp[i][j][k + 1] = (tmp[i][j][k + 1] + dp[i][j][k]) % MOD;
                        }
                    }
                    
                }
            }
        }

        // DEBUG
        // for (int i = 0; i <= n; i++) {
        //     for (int j = 0; j <= n; j++) {
        //         for (int k = 0; k <= n; k++) {
        //             if (!tmp[i][j][k]) continue;
        //             cout << l << ' ' << i << ' ' << j << ' ' << k << ' ' << tmp[i][j][k] << '\n';
        //         }
        //     }
        // }
        // cout << '\n';
        
        dp.swap(tmp);
    }

    cout << dp[n][n][n] << '\n';
}
