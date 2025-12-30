#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n, k;
        cin >> n >> k;
        
        vector<int> stk;
        vector<int> idx;
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            if (x > 0 && (stk.empty() || (stk.back() < x))) {
                stk.push_back(x);
                idx.push_back(i);
            }
        }

        vector<vector<int>> dp(k + 1, vector<int>(k + 1));

        // base case
        dp[0][0] = 0;

        // inductive step
        for (int t = 0; t < sz(stk); t++) {
            int cnt = n - idx[t];
            for (int x = (t == 0 ? 0 : stk[t - 1]); x <= stk[t]; x++) {
                for (int i = 0; i < x; i++) {
                    for (int j = i; j <= k - x; j++) {
                        dp[x][j + x] = max(dp[x][j + x], dp[i][j] + (x - i) * cnt);
                    }
                }
            }
        }

        int ans = 0;
        for (int i = 0; i <= k; i++) {
            for (int j = 0; j <= k; j++) {
                ans = max(ans, dp[i][j]);
                // cout << i << ' ' << j << ' ' << dp[i][j] << '\n';
            }
        }
        cout << ans << '\n';
    }
}