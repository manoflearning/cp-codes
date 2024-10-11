#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 1010;

int n, m;
vector<int> adj[MAXN];
ll ans = 0;

bool vis[MAXN];
int dfs(int v) {
    int ret = 1;
    vis[v] = 1;
    for (auto& i : adj[v]) {
        if (!vis[i]) ret += dfs(i);
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

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[v].push_back(u);
    }

    ans += (ll)n * (n - 1) / 2;

    for (int v = 1; v <= n; v++) {
        memset(vis, 0, sizeof(vis));
        ans -= dfs(v) - 1;
    }

    cout << ans;
}
