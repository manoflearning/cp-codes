#include <bits/stdc++.h>
using namespace std;

const int MAXN = 202020;
const int MAXV = 1010101;

int n, a[MAXN][2];
struct Edge { int id, v; };
vector<Edge> adj[MAXV];

bool vis[MAXV];

pair<int, bool> dfs(int v, int prv) {
    vis[v] = 1;
    pair<int, bool> ret = {1, 1};
    for (auto [id, u] : adj[v]) {
        if (id == prv) continue;

        if (!vis[u]) {
            auto res = dfs(u, id);
            ret.first += res.first;
            ret.second &= res.second;
        } else ret.second = 0;
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i][0];
    for (int i = 0; i < n; i++) cin >> a[i][1];

    for (int i = 0; i < n; i++) {
        int u = a[i][0], v = a[i][1];
        adj[u].push_back({i, v});
        adj[v].push_back({i, u});
    }

    int ans = 0;
    for (int v = 0; v < MAXV; v++) {
        if (!vis[v]) {
            auto [siz, is_tree] = dfs(v, -1);
            if (is_tree) ans += siz - 1;
            else ans += siz;
        }
    }
    
    cout << ans;
}
