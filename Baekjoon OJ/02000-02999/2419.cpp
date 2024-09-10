#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;

int n, m;
vector<int> xs;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    xs.resize(n);
    for (auto& i : xs) cin >> i;

    sort(all(xs));

    int ans = 0;
    for (int candy_to_eat = 1; candy_to_eat <= n; candy_to_eat++) {
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(2, -INF)));

        // base case
        for (int i = 0; i < n; i++) {
            dp[i][i][0] = m - abs(xs[i]) * candy_to_eat;
            dp[i][i][1] = m - abs(xs[i]) * candy_to_eat;
        }

        // inductive step
        for (int len = 1; len < candy_to_eat; len++) {
            for (int lb = 0, ub = len - 1; ub < n; lb++, ub++) {
                if (0 <= lb - 1) {
                    dp[lb - 1][ub][0] = max(
                        dp[lb - 1][ub][0],
                        dp[lb][ub][0] + m - abs(xs[lb] - xs[lb - 1]) * (candy_to_eat - len)
                    );
                    dp[lb - 1][ub][0] = max(
                        dp[lb - 1][ub][0],
                        dp[lb][ub][1] + m - abs(xs[ub] - xs[lb - 1]) * (candy_to_eat - len)
                    );
                }
                if (ub + 1 < n) {
                    dp[lb][ub + 1][1] = max(
                        dp[lb][ub + 1][1],
                        dp[lb][ub][0] + m - abs(xs[lb] - xs[ub + 1]) * (candy_to_eat - len)
                    );
                    dp[lb][ub + 1][1] = max(
                        dp[lb][ub + 1][1],
                        dp[lb][ub][1] + m - abs(xs[ub] - xs[ub + 1]) * (candy_to_eat - len)
                    );
                }
            }
        }

        // get result
        for (int i = 0; i + candy_to_eat - 1 < n; i++) {
            ans = max(ans, dp[i][i + candy_to_eat - 1][0]);
            ans = max(ans, dp[i][i + candy_to_eat - 1][1]);
        }
    }
    
    cout << ans;
}