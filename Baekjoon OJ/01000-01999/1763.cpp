#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAXN = 1010;
const ll INF = 1e18;

int n, ro;
ll c[MAXN];
vector<int> adj[MAXN];

int siz[MAXN];
vector<int> arr[MAXN];

void input() {
    cin >> n >> ro;
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void dfs(int v, int prv) {
    siz[v] = 1;
    arr[v].push_back(v);

    for (auto& u : adj[v]) {
        if (u == prv) continue;
        dfs(u, v);

        vector<vector<ll>> dp(siz[v] + 1, vector<ll>(siz[u] + 1, INF));
        // base case
        dp[1][0] = c[v];
        // inductive step
        for (int i = 1; i <= siz[v]; i++) {
            for (int j = 0; j <= siz[u]; j++) {
                int f = i + j + 1;
                int p = arr[v][i], q = arr[u][j];

                if (i + 1 <= siz[v]) dp[i + 1][j] = min(dp[i + 1][j], c[p] * f + dp[i][j]);
                if (j + 1 <= siz[u]) dp[i][j + 1] = min(dp[i][j + 1], c[q] * f + dp[i][j]);
            }
        }
        // backtrace
        vector<int> tmp(siz[v] + siz[u]);
        int i = siz[v], j = siz[u];
        while (i >= 2 || j >= 1) {
            int f = i + j;
            if (i >= 2 && j >= 1) {
                int p = arr[v][i - 1], q = arr[u][j - 1];
                if (dp[i][j] == dp[i - 1][j] + c[p] * f) {
                    tmp[f - 1] = p, i--;
                } else if (dp[i][j] == dp[i][j - 1] + c[q] * f) {
                    tmp[f - 1] = q, j--;
                } else assert(0);
            }
            else if (i >= 2) tmp[f - 1] = arr[v][i - 1], i--;
            else if (j >= 1) tmp[f - 1] = arr[u][j - 1], j--;
            else assert(0);
        }
        tmp[0] = v;

        arr[v] = tmp;
        siz[v] += siz[u];
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

    dfs(ro, 0);

    ll ans = 0;
    for (int i = 0; i < sz(arr[ro]); i++) {
        int v = arr[ro][i];
        ans += c[v] * (i + 1);
        // cout << v << ' ';
    }
    // cout << '\n';

    cout << ans;
}
