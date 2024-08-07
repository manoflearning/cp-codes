#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n;
struct Edge { ll w; int v; };
vector<Edge> adj[303030];
ll dp1[303030], dp2[303030], siz[303030];

void input() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
}

void dfs1(int v, int prv) {
    siz[v] = 1;
    for (auto& i : adj[v]) {
        if (i.v == prv) continue;
        dfs1(i.v, v);
        dp1[v] += dp1[i.v] + i.w * siz[i.v];
        siz[v] += siz[i.v];
    }
}

void dfs2(int v, int prv) {
    // dp2[v] += (prv != -1 ? dp2[prv] : 0);
    for (auto& i : adj[v]) {
        if (i.v == prv) continue;
        dp2[i.v] += dp2[v] + dp1[v] - (dp1[i.v] + i.w * siz[i.v]) + i.w * (n - siz[i.v]);
        dfs2(i.v, v);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    dfs1(1, -1);
    dfs2(1, -1);

    for (int v = 1; v <= n; v++) {
        cout << dp1[v] + dp2[v] << '\n';
    }
}