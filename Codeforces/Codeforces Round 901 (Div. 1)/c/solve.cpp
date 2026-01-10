#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
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

constexpr int INF = 1e9 + 7;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
        }

        vector<ld> dp(n + 1);
        dp[n] = 1;

        for (int u = n - 1; u >= 1; u--) {
            if (adj[u].empty()) continue;

            sort(all(adj[u]), [&](int i, int j) {
                return dp[i] > dp[j];
            });

            ld already = 0;

            ld p = sz(adj[u]) - !(sz(adj[u]) & 1);
            p = 1 / p;
            // for (int i = 0; 2 * i + 1 < sz(adj[u]); i++) {
            //     p /= 2;
            // }
            // cout << u << ' ' << p << '\n';
            for (int i = 0; i + !(sz(adj[u]) & 1) < sz(adj[u]); i++) {
                const int v = adj[u][i];
                
                // ld res = 1 - already;
                // res *= (ld)1 / (sz(adj[u]) - i);

                dp[u] += p * dp[v];
                // if (u == 1)
                //     cout << v << ' ' << res << '\n';
                
                if (i & 1) p /= 2;
            }
            // cout << u << ' ' << dp[u] << '\n';

            // if (sz(adj[u]) & 1) {
            //     for (int v : adj[u]) {
            //         dp[u] += (ld)1 / sz(adj[u]) * dp[v];
            //     }
            // } else {
            //     // ld p_fail = 1;
            //     // for (int t = 1; 2 * t <= sz(adj[u]); t++) {
            //     //     p_fail *= 2 * t - 1;
            //     //     p_fail /= 2 * t;
            //     // }

            //     sort(all(adj[u]), [&](int i, int j) {
            //         return dp[i] > dp[j];
            //     });

            //     const ll m = sz(adj[u]);
            //     for (int i = 0; i < sz(adj[u]) - 1; i++) {
            //         const int v = adj[u][i];

            //         ld res = 1 - p_fail;
            //         res *= (m - i - 1);
            //         res /= m * (m - 1) / 2;
            //         // res /= 2;
            //         dp[u] += res * dp[v];
            //     }
            // }
        }

        cout << fixed;
        cout.precision(10);

        cout << dp[1] << '\n';
    }
}
