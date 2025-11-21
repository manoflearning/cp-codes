#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int N = 202020;

int n, m, k;
int a[N];
vector<int> adj[N];
int dist[N], ans[N];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(dist, -1, sizeof(dist));

    queue<int> qu;
    dist[1] = 0;
    qu.push(1);

    while (!qu.empty()) {
        int v = qu.front();
        qu.pop();

        ans[a[v]] = max(ans[a[v]], dist[v]);

        for (const auto u : adj[v]) {
            if (dist[u] != -1) continue;
            dist[u] = dist[v] + 1;
            qu.push(u);
        }
    }

    for (int i = 1; i <= k; i++) {
        cout << ans[i] << ' ';
    }
}