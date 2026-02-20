#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vl = vector<ll>;

constexpr ll INF = 4e18;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vector<ll> d(n);
    for (auto &i : d) cin >> i;

    vector<int> ord(n);
    iota(all(ord), 0);
    sort(all(ord), [&](int i, int j) {
        return d[i] > d[j];
    });

    vector<vector<ll>> dp(n, vector<ll>(m, INF));
    vector<vector<vector<int>>> opt(m, vector<vector<int>>(n));

    opt.shrink_to_fit();
    for (int k = 0; k < m; k++) {
        opt[k].shrink_to_fit();
        for (int i = 0; i < n; i++) {
            opt[k][i].assign(i + 1, -1);
            opt[k][i].shrink_to_fit();
        }
    }

    // base case
    dp[0][0] = 0;

    // inductive step
    for (int i = 0; i + 1 < n; i++) {
        vector<vector<ll>> tmp(n, vector<ll>(m, INF));

        for (int j = 0; j <= i; j++) {
            for (int k = 0; k < m; k++) {
                if (dp[j][k] == INF) continue;

                if (tmp[j][k] > dp[j][k] + (d[ord[i + 1]] - d[ord[j]]) * (d[ord[i + 1]] - d[ord[j]])) {
                    tmp[j][k] = dp[j][k] + (d[ord[i + 1]] - d[ord[j]]) * (d[ord[i + 1]] - d[ord[j]]);
                    opt[k][i + 1][j] = j;
                }
                if (k + 1 < m && tmp[i + 1][k + 1] > dp[j][k]) {
                    tmp[i + 1][k + 1] = dp[j][k];
                    opt[k + 1][i + 1][i + 1] = j;
                }
            }
        }
        dp = tmp;
    }

    int opt_j = -1, opt_k = -1;
    for (int j = 0; j < n; j++) {
        for (int k = 0; k < m; k++) {
            if (opt_j == -1 || dp[j][k] < dp[opt_j][opt_k]) {
                opt_j = j, opt_k = k;
            }
        }
    }

    vector<ll> ans(n);
    for (int i = n - 1; i >= 0; i--) {
        ans[ord[i]] = d[ord[opt_j]];
        if (opt_j != opt[opt_k][i][opt_j]) {
            opt_j = opt[opt_k][i][opt_j];
            opt_k--;
        }
    }

    for (auto &i : ans) cout << i << ' ';
    cout << '\n';
}
