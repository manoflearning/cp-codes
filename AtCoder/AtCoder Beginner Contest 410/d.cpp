#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 1010;

int n, m;
struct Edge {
    int v, w;
};
vector<Edge> adj[N];

int dist[N][1 << 10];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    memset(dist, -1, sizeof(dist));

    queue<pii> qu;
    qu.push({1, 0});
    dist[1][0] = 0;
    while (!qu.empty()) {
        auto [v, w] = qu.front();
        qu.pop();

        for (auto &i : adj[v]) {
            if (dist[i.v][w ^ i.w] != -1) continue;
            qu.push({i.v, w ^ i.w});
            dist[i.v][w ^ i.w] = 1 + dist[v][w];
        }
    }

    for (int bit = 0; bit < (1 << 10); bit++) {
        if (dist[n][bit] != -1) {
            cout << bit;
            exit(0);
        }
    }
    cout << -1;
}
