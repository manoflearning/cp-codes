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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n, tot;
        cin >> n >> tot;

        vector<int> a(n);
        for (auto &i : a) cin >> i;

        vector<int> stk;
        for (int i = 0; i < n; i++) {
            if (stk.empty() && 0 < a[i]) {
                stk.push_back(i);
            } else if (!stk.empty() && a[stk.back()] < a[i]) {
                stk.push_back(i);
            }
        }

        assert(sz(stk) <= tot);

        if (stk.empty()) {
            cout << 0 << '\n';
            continue;
        }

        vector<vector<vector<int>>> dp(
            sz(stk), vector<vector<int>>(
                tot + 1, vector<int>(
                    tot + 1, -1
                )
            )
        );

        // base case
        for (int i = 0; i <= a[stk[0]]; i++) {
            dp[0][i][i] = (n - stk[0]) * i;
        }

        // inductive step
        for (int i = 1; i < sz(stk); i++) {
            for (int j = 0; j <= a[stk[i - 1]]; j++) {
                for (int k = j; k <= tot; k++) {
                    dp[i][j][k] = dp[i - 1][j][k];
                }
            }

            for (int j = a[stk[i - 1]] + 1; j <= a[stk[i]]; j++) {
                for (int k = j; k <= tot; k++) {
                    int prv_k = k - j;
                    for (int prv_j = 0; prv_j < j; prv_j++) {
                        if (dp[i - 1][prv_j][prv_k] == -1) continue;

                        int res = 0;

                        res += dp[i - 1][prv_j][prv_k];
                        res += (n - stk[i]) * (j - prv_j);

                        dp[i][j][k] = max(dp[i][j][k], res);
                    }    
                }
            }
        }

        // DEBUG
        // for (int i = 0; i < sz(stk); i++) {
        //     for (int j = 0; j <= tot; j++) {
        //         for (int k = j; k <= tot; k++) {
        //             cout << "dp[" << i << "][" << j << "][" << k << "] = " << dp[i][j][k] << '\n';
        //         }
        //     }
        // }

        int ans = 0;
        for (int j = 0; j <= tot; j++) {
            for (int k = j; k <= tot; k++) {
                ans = max(ans, dp[sz(stk) - 1][j][k]);

                // cout << j << ' ' << k << ' ' << dp[sz(stk) - 1][j][k] << '\n';
            }
        }
        cout << ans << '\n';
    }
}

// if i < j and b[i] >= b[j] => set b[j] := 0
// if i < j and a[i] >= a[j] => set a[j] := 0