#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll INF = 1e18;

int n;
ll adj[1010][1010];

void init() {
    for (int i = 0; i < 1010; i++) {
        for (int j = 0; j < 1010; j++) {
            adj[i][j] = (i ^ j ? INF : 0);
        }
    }
}

void input() {
    int ml, md;
    cin >> n >> ml >> md;
    while (ml--) {
        int u, v; ll w;
        cin >> u >> v >> w;
        // x_v - x_u <= w
        adj[u][v] = min(adj[u][v], w);
    }
    while (md--) {
        int u, v; ll w;
        cin >> u >> v >> w;
        // x_v - x_u >= w iff x_u - x_v <= -w
        adj[v][u] = min(adj[v][u], -w);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    init();

    input();

    for (int v = 1; v < n; v++) {
        // x_{v + 1} - x_v >= 0
        // iff x_v - x_{v + 1} <= 0
        adj[v + 1][v] = min(adj[v + 1][v], 0ll);
    }

    for (int k = 1; k <= n; k++) {
        for (int u = 1; u <= n; u++) {
            if (adj[u][k] == INF) continue;
            for (int v = 1; v <= n; v++) {
                adj[u][v] = min(adj[u][v], adj[u][k] + adj[k][v]);
            }
        }
    }

    for (int v = 1; v <= n; v++) {
        if (adj[v][v] < 0) {
            cout << -1;
            return 0;
        }
    }

    if (adj[1][n] == INF) {
        cout << -2;
        return 0;
    }

    cout << adj[1][n];
}