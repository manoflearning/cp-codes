#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll INF = 1e18;

int n, K;
struct Edge { ll w; int v; };
vector<Edge> adj[1010];

int siz[1010];
ll dp[1010][1010][2];

void input() {
    cin >> n >> K;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
}

void dfs(int v, int prv) {
    siz[v] = 1;
    dp[v][0][0] = 0;
    dp[v][1][1] = 0;

    for (auto& i : adj[v]) {
        if (i.v == prv) continue;
        dfs(i.v, v);

        vector<vector<ll>> tmp(siz[v] + siz[i.v] + 1, vector<ll>(2, INF));
        for (int p = 0; p <= siz[v]; p++) {
            for (int q = 0; q <= siz[i.v]; q++) {
                tmp[p + q][0] = min(tmp[p + q][0], dp[v][p][0] + dp[i.v][q][0] + i.w);
                tmp[p + q][0] = min(tmp[p + q][0], dp[v][p][0] + dp[i.v][q][1]);

                tmp[p + q][1] = min(tmp[p + q][1], dp[v][p][1] + dp[i.v][q][0]);
                tmp[p + q][1] = min(tmp[p + q][1], dp[v][p][1] + dp[i.v][q][1] + i.w);
            }
        }

        for (int p = 0; p <= siz[v] + siz[i.v]; p++) {
            dp[v][p][0] = tmp[p][0];
            dp[v][p][1] = tmp[p][1];
        }

        siz[v] += siz[i.v];
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    for (int i = 0; i < 1010; i++)
        for (int j = 0; j < 1010; j++)
            dp[i][j][0] = dp[i][j][1] = INF;

    input();

    dfs(1, 0);

    cout << min(dp[1][K][0], dp[1][K][1]) << '\n';
}
