#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAXN = 303;
const int D = 303;
const int INF = 1e9 + 7;

int n, d;
int co[MAXN];
vector<int> chd[MAXN];

vector<ll> dp[MAXN];

void input() {
    cin >> n >> d;
    for (int i = 0; i < n; i++) {
        int v, m;
        cin >> v >> co[v] >> m;
        if (co[v] == 0) co[v] = -1;
        chd[v].resize(m);
        for (auto &j : chd[v]) cin >> j;
    }
}

void dfs(int v) {
    // base case
    dp[v].resize(D << 1, INF);
    dp[v][D + co[v]] = min(dp[v][D + co[v]], 0ll);
    // inductive step
    for (auto u : chd[v]) {
        dfs(u);
        vector<ll> tmp(D << 1, INF);
        for (int i = 0; i < sz(dp[v]); i++) {
            if (dp[v][i] == INF) continue;
            tmp[i] = min(tmp[i], 1 + dp[v][i]);
            for (int j = 0; j < sz(dp[u]); j++) {
                if (dp[u][j] == INF) continue;
                int k = i + j - D;
                assert(0 <= k && k < (D << 1));
                tmp[k] = min(tmp[k], dp[v][i] + dp[u][j]);
            }
        }
        dp[v] = tmp;
    }
    dp[v][D] = min(dp[v][D], 1ll);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    dfs(0);
    // cout << dp[0][D] << ' ' << dp[0][D + 1] << ' ' << dp[0][D + 2] << '\n';
    cout << (dp[0][D + d] == INF ? -1 : dp[0][D + d]);
}
