#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int n;
vector<vector<int>> dp;
vector<vector<vector<int>>> adj, radj;

void f(int u, int v) {
    if (dp[u][v] != -1) return;
    dp[u][v] = 1;
    for (int c = 0; c < 26; c++)
        for (const int p : radj[c][u])
            for (const int q : adj[c][v]) f(p, q);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    adj.assign(26, vector<vector<int>>(n));
    radj.assign(26, vector<vector<int>>(n));
    for (int i = 0; i < m; i++) {
        int u, v; char w;
        cin >> u >> v >> w;
        u--, v--;
        adj[w - 'a'][u].push_back(v);
        radj[w - 'a'][v].push_back(u);
    }

    dp.assign(n, vector<int>(n, -1));
    for (int i = 0; i < n; i++) {
        f(i, i);
        for (int c = 0; c < 26; c++)
            for (const int j : adj[c][i]) f(i, j);
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ans += dp[i][j] == 1 && i != j;
    cout << ans << '\n';
}
