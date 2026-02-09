#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

struct Edge { int nxt, x; };

void dfs(int now, int acc, const vector<vector<Edge>> &adj, vector<bool> &vis, int &ans) {
    vis[now] = 1;
    ans ^= acc;
    for (const Edge &e : adj[now]) {
        if (!vis[e.nxt]) dfs(e.nxt, acc ^ e.x, adj, vis, ans);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;

        vector<vector<Edge>> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v, x;
            cin >> u >> v >> x;
            u--, v--;
            adj[u].push_back({v, x});
            adj[v].push_back({u, x});
        }

        if (n & 1) {
            cout << -1 << '\n';
            continue;
        }

        int ans = 0;
        for (int i = 0; i <= n; i++) ans ^= i;
        
        vector<bool> vis(n);
        dfs(0, 0, adj, vis, ans);

        cout << ans << '\n';
    }

    return 0;
}
