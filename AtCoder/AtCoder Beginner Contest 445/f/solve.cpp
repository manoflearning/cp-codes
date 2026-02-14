#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ll INF = 4e18;
constexpr int D = 32;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, k;
    cin >> n >> k;
    vector<vector<ll>> c(n, vector<ll>(n));
    for (auto &i : c) for (auto &j : i) cin >> j;

    vector<vector<vector<ll>>> dp(D, vector<vector<ll>>(n, vector<ll>(n, INF)));
    // base case
    dp[0] = c;
    // inductive step
    for (int d = 0; d + 1 < D; d++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    dp[d + 1][i][j] = min(dp[d + 1][i][j], dp[d][i][k] + dp[d][k][j]);
                }
            }
        }
    }

    vector<vector<ll>> ans(n, vector<ll>(n, INF));
    for (int i = 0; i < n; i++) ans[i][i] = 0;
    for (int d = 0; d < D; d++) {
        if (~k & (1ll << d)) continue;

        vector<vector<ll>> tmp(n, vector<ll>(n, INF));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    tmp[i][j] = min(tmp[i][j], ans[i][k] + dp[d][k][j]);
                }
            }
        }
        ans = std::move(tmp);
    }

    for (int i = 0; i < n; i++) cout << ans[i][i] << '\n';

    return 0;
}
