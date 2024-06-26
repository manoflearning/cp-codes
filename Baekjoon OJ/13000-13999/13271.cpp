#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll INF = 1e18;

int N, K;
struct wv { int w, v; };
vector<wv> adj[1010];
vector<ll> upper(1010, INF);

void input() {
    cin >> N >> K;
    for (int i = 0; i < K; i++) {
        int op, u, v, w;
        cin >> op >> u >> v >> w;
        if (op == 1) {
            // x_u - x_v >= w
            // iff x_v - x_u <= w
            adj[u].push_back({ -w, v });
        }
        if (op == 2) {
            // x_u - x_v <= w
            adj[v].push_back({ w, u });
        }
        if (op == 3) {
            // x_u - x_v = w
            // iff x_u - x_v <= w and x_v - x_u <= -w
            adj[v].push_back({ w, u });
            adj[u].push_back({ -w, v });
        }
    }
}

int bellmanFord() {
    upper[0] = 0;
    int update = 1;
    for (int i = 0; i < N + 2; i++) {
        update = 0;
        for (int now = 0; now <= N; now++) {
            if (upper[now] == INF) continue;
            for (wv e : adj[now]) {
                int next = e.v;
                if (upper[next] > upper[now] + e.w) {
                    upper[next] = upper[now] + e.w;
                    update = 1;
                }
            }
        }
        if (!update) break;
    }
    return !update;
}

int main() {
    input();

    for (int i = 1; i <= N; i++)
        adj[0].push_back({ 0, i });

    if (bellmanFord()) {
        ll mn = INF, mx = -INF;
        for (int i = 1; i <= N; i++) {
            mn = min(mn, upper[i]);
            mx = max(mx, upper[i]);
        }
        
        cout << (mx - mn <= 100 ? mx - mn : -1);
    }
    else cout << -1;
}