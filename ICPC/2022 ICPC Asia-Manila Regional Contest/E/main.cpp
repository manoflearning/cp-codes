#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int N = 202020;
constexpr ll INF = 1e18;

int n, m, p, l;
vector<int> adj[N];
vector<unordered_set<ll>> banned;
int st, en;
ll dist[N];

void input() {
    cin >> n >> m >> p >> l;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    banned.resize(l);
    for (int i = 0; i < p; i++) {
        vector<int> b(l);
        for (auto &j : b) cin >> j;
        for (int j = 0; j < l; j++) {
            ll h = min<ll>(b[j], b[(j + 1) % l]) * N + max(b[j], b[(j + 1) % l]);
            banned[j].insert(h);
        }
    }
    cin >> st >> en;
}

void dijkstra() {
    for (int i = 0; i < N; i++) dist[i] = INF;
    
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

    dist[st] = 0;
    pq.push({dist[st], st});

    while (!pq.empty()) {
        auto [w, v] = pq.top();
        pq.pop();

        if (w != dist[v]) continue;

        // cout << w << ' ' << v << '\n';

        for (int u : adj[v]) {
            for (ll nw = w + 1; nw <= w + l; nw++) {
                ll h = min<ll>(u, v) * N + max(u, v);
                if (banned[(nw + l - 1) % l].count(h)) continue;

                if (nw < dist[u]) {
                    dist[u] = nw;
                    pq.push({dist[u], u});
                }

                break;
            }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    input();

    dijkstra();

    if (dist[en] == INF) cout << "IMPOSSIBLE";
    else cout << dist[en];
}
