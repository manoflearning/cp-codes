#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

constexpr ll INF = 1e18;

int n, m;
vi p;
vector<ll> v;
vector<vector<ll>> dp;
vector<vector<bool>> vis;
vector<bool> pp, np;

void dfs(int i, int j) {
    if (i == 0) return;

    vis[i][j] = 1;

    if (dp[i - 1][j] == dp[i][j]) {
        np[i] = 1;
        if (!vis[i - 1][j]) dfs(i - 1, j);
    }
    if (j >= p[i] && dp[i - 1][j - p[i]] + v[i] == dp[i][j]) {
        pp[i] = 1;
        if (!vis[i - 1][j - p[i]]) dfs(i - 1, j - p[i]);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    cin >> n >> m;
    p.assign(n + 1, 0);
    v.assign(n + 1, 0);
    for (int i = 1; i <= n; i++)
        cin >> p[i] >> v[i];

    dp.assign(n + 1, vector<ll>(m + 1, -INF));

    // base case
    dp[0][0] = 0;

    // inductive step
    for (int i = 0; i + 1 <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (dp[i][j] == -INF) continue;

            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
            if (j + p[i + 1] <= m)
                dp[i + 1][j + p[i + 1]] = max(dp[i + 1][j + p[i + 1]], dp[i][j] + v[i + 1]);
        }
    }

    ll opt = -INF;
    for (int i = 0; i <= m; i++) opt = max(opt, dp[n][i]);

    vis.assign(n + 1, vector<bool>(m + 1, 0));
    pp.assign(n + 1, 0);
    np.assign(n + 1, 0);
    for (int i = 0; i <= m; i++) {
        if (opt != dp[n][i]) continue;
        dfs(n, i);
    }

    for (int i = 1; i <= n; i++) {
        if (pp[i] && np[i]) cout << "B";
        else if (pp[i]) cout << "A";
        else if (np[i]) cout << "C";
        else assert(0);
    }
}
