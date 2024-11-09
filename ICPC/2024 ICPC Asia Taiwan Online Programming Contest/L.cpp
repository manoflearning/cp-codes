#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAXN = 55;
const ll INF = 1e18;
const int MAXD = 30;

const int MOD = 1e9 + 7;

int n, m, s, t, x, k;
vector<pair<ll, int>> adj[MAXN];

ll dp[MAXN][MAXN][MAXD + 1];

void input() {
    cin >> n >> m >> s >> t >> x >> k;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
    }
}

ll power(ll x, ll y) {
    if (y == 0) return 1;
    if (y == 1) return x;
    ll res = power(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

void build_sp() {
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            for (int p = 0; p <= MAXD; p++) {
                dp[i][j][p] = INF;
            }
        }
    }

    // base case
    for (int v = 1; v <= n; v++) {
        for (auto [w, u] : adj[v]) {
            dp[v][u][0] = min(dp[v][u][0], w);
        }
    }

    // inductive step
    for (int i = 1; i <= MAXD; i++) {
        for (int v = 1; v <= n; v++) {
            for (int p = 1; p <= n; p++) {
                if (dp[v][p][i - 1] == INF) continue;
                for (int u = 1; u <= n; u++) {
                    if (dp[p][u][i - 1] == INF) continue;
                    ll res = 0;
                    res += dp[v][p][i - 1] * power(x, (1 << (i - 1)));
                    res %= MOD;
                    res += dp[p][u][i - 1];
                    res %= MOD;
                    dp[v][u][i] = min(dp[v][u][i], res);
                }
            }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    build_sp();


}
