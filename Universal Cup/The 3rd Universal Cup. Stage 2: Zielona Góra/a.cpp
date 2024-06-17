#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int N = 1010101, M = 1010101;

int n, m;
vector<int> adj[N], radj[N], nadj[N];
int ind[N], forb[N];

void input() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        radj[v].push_back(u);
    }
}

int vis[N];

void dfs(int v, int bit) {
    vis[v] = 1;
    for (auto& i : (bit ? adj[v] : radj[v])) {
        if (!vis[i]) dfs(i, bit);
    }
}

void node_del() {
    // forward
    dfs(1, 1);

    for (int v = 1; v <= n; v++)
        if (!vis[v]) forb[v] = 1;
    
    if (!vis[n]) { cout << 0; exit(0); }

    // backward
    memset(vis, 0, sizeof(vis));

    dfs(n, 0);

    for (int v = 1; v <= n; v++)
        if (!vis[v]) forb[v] = 1;

    for (int v = 1; v <= n; v++) {
        if (forb[v]) continue;
        for (auto& i : adj[v]) {
            if (forb[i]) continue;
            nadj[v].push_back(i);
            ind[i]++;
        }
    }
}

ll dp[N];
void solve() {
    queue<int> q;
    q.push(1);
    dp[1] = 1;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (auto& i : nadj[v]) {
            // if (forb[i]) continue;

            dp[i] += dp[v];
            dp[v] = min(dp[v], 1ll);

            ind[i]--;
            if (!ind[i]) q.push(i);
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

    node_del();

    solve();

    cout << dp[n];
}