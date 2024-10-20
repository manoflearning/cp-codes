#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

struct wv {
    int w, v;
    bool operator<(const wv& rhs) const {
        return w > rhs.w;
    }
};

int n, m;
vector<wv> adj[222];

void input() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ 2 * w, v });
        adj[v].push_back({ 2 * w, u });
    }
}

int dijkstra(int st) {
    priority_queue<wv> pq;
    pq.push({ 0, st });
    vector<int> dist(n + 1, INF);
    dist[st] = 0;

    int ret = 0;
    while (!pq.empty()) {
        auto [w, v] = pq.top();
        pq.pop();

        if (dist[v] < w) continue;
        ret = max(ret, w);

        for (auto& i : adj[v]) {
            int nw = w + i.w;
            if (nw < dist[i.v]) {
                dist[i.v] = nw;
                pq.push({ nw, i.v });
            }
            /*else if (w <= dist[i.v]) {
                ret = max(ret, w + i.w / 2);
            }*/
        }
    }

    for (int v = 1; v <= n; v++) {
        for (auto& i : adj[v]) {
            int w = i.w, u = i.v;
            if (dist[v] <= dist[u] && dist[u] < dist[v] + w) {
                ret = max(ret, (dist[v] + dist[u] + w) / 2);
            }
        }
    }

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif
    
    input();

    int ans = INF;
    for (int v = 1; v <= n; v++)
        ans = min(ans, dijkstra(v));

    cout << ans / 2 << (ans & 1 ? ".5\n" : ".0");
}