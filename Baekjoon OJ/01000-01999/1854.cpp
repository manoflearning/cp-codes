#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAXN = 1010;

int n, m, k;
struct Edge { ll w; int v; };
vector<Edge> adj[MAXN];

priority_queue<ll> dist[MAXN];

void input() {
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
    }
}

void kth_dijkstra() {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

    dist[1].push(0);
    pq.push({ 0, 1 });

    while (!pq.empty()) {
        auto [w, v] = pq.top();
        pq.pop();

        if (sz(dist[v]) == k && dist[v].top() < w) continue;

        for (auto& i : adj[v]) {
            if (sz(dist[i.v]) == k) {
                if (w + i.w < dist[i.v].top()) {
                    dist[i.v].pop();
                    dist[i.v].push(w + i.w);
                    pq.push({ w + i.w, i.v });
                } else continue;
            } else {
                dist[i.v].push(w + i.w);
                pq.push({ w + i.w, i.v });
            }
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

    kth_dijkstra();

    for (int i = 1; i <= n; i++) {
        if (sz(dist[i]) == k) cout << dist[i].top() << '\n';
        else cout << -1 << '\n';
    }
}
