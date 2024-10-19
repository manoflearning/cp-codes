#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;

int n, m;
vector<vector<int>> adj(202020), radj(202020);

vector<int> dist(202020, -1), rdist(202020, -1);

void bfs(const vector<vector<int>>& grh, vector<int>& d) {
    queue<int> q;
    d[1] = 0;
    q.push(1);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto& i : grh[v]) {
            if (d[i] != -1) continue;
            d[i] = d[v] + 1;
            q.push(i);
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

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        radj[v].push_back(u);
    }

    bfs(adj, dist);
    bfs(radj, rdist);

    int ans = INF;
    for (int i = 2; i <= n; i++) {
        if (dist[i] != -1 && rdist[i] != -1) {
            ans = min(ans, dist[i] + rdist[i]);
        }
    }

    cout << (ans == INF ? -1 : ans);
}
