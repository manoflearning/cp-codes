#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAXN = 50505;
const ll INF = 1e18;

struct Edge {
    int v; ll w, g;
};

int n, m;
vector<Edge> adj[MAXN];

ll dist[MAXN];
vector<Edge> dag[MAXN];
bool vis[MAXN];

ll dist1[2][MAXN], gsum[2][MAXN];

ll dp2[MAXN];

void init() {
    for (int i = 0; i < MAXN; i++) {
        adj[i].clear();
        dag[i].clear();
        dist[i] = INF;
        dist1[0][i] = dist1[1][i] = INF;
    }

    memset(vis, 0, sizeof(vis));
    memset(gsum, 0, sizeof(gsum));
    memset(dp2, -1, sizeof(dp2));
}

void input() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; ll w, g;
        cin >> u >> v >> w >> g;
        adj[u].push_back({ v, w, g });
        adj[v].push_back({ u, w, g });
    }
}

void dijkstra() {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;

    dist[1] = 0;
    pq.push({ dist[1], 1 });

    while (!pq.empty()) {
        auto [w, v] = pq.top();
        pq.pop();
        if (dist[v] < w) continue;
        for (auto& i : adj[v]) {
            if (w + i.w < dist[i.v]) {
                dist[i.v] = w + i.w;
                pq.push({ dist[i.v], i.v });
            }
        }
    }
}

void btrc(int v) {
    vis[v] = 1;
    for (auto& i : adj[v]) {
        if (dist[i.v] + i.w == dist[v]) {
            dag[i.v].push_back({ v, i.w, i.g });
            if (!vis[i.v]) btrc(i.v);
        }
    }
}

void dijkstra1() {
    priority_queue<tuple<ll, bool, int>, vector<tuple<ll, bool, int>>, greater<tuple<ll, bool, int>>> pq;

    dist1[0][1] = 0;
    gsum[0][1] = 0;
    pq.push({ dist1[0][1], 0, 1 });

    while (!pq.empty()) {
        auto [w, bit, v] = pq.top();
        pq.pop();

        if (dist1[bit][v] < w) continue;

        if (bit == 0) {
            for (auto& i : dag[v]) {
                if (dist1[0][i.v] > w + i.w) {
                    dist1[0][i.v] = w + i.w;
                    gsum[0][i.v] = gsum[0][v] + i.g;
                    pq.push({ dist1[0][i.v], 0, i.v });
                } else if (dist1[0][i.v] == w + i.w && gsum[0][i.v] < gsum[0][v] + i.g) {
                    gsum[0][i.v] = gsum[0][v] + i.g;
                }
            }
            for (auto& i : adj[v]) {
                if (dist[i.v] == dist[v] + i.w && vis[i.v]) continue;

                if (dist1[1][i.v] > w + i.w) {
                    dist1[1][i.v] = w + i.w;
                    gsum[1][i.v] = gsum[0][v] + i.g;
                    pq.push({ dist1[1][i.v], 1, i.v });
                } else if (dist1[1][i.v] == w + i.w && gsum[1][i.v] < gsum[0][v] + i.g) {
                    gsum[1][i.v] = gsum[0][v] + i.g;
                } 
            }
        } else {
            for (auto& i : adj[v]) {
                if (w + i.w < dist1[1][i.v]) {
                    dist1[1][i.v] = w + i.w;
                    gsum[1][i.v] = gsum[1][v] + i.g;
                    pq.push({ dist1[1][i.v], 1, i.v });
                } else if (dist1[1][i.v] == w + i.w && gsum[1][i.v] < gsum[1][v] + i.g) {
                    gsum[1][i.v] = gsum[1][v] + i.g;
                } 
            }
        }
    }
}

ll case2(int v) {
    auto& ret = dp2[v];
    if (ret != -1) return ret;
    if (v == n) return ret = 0;
    ret = 0;
    for (auto& i : dag[v]) {
        ret = max(ret, i.g + case2(i.v));
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        init();

        input();

        dijkstra();

        btrc(n);

        bool is_linear = 1;
        int v = 1;
        while (!dag[v].empty()) {
            if (sz(dag[v]) >= 2) is_linear = 0;
            v = dag[v][0].v;
        }
        assert(v == n);

        ll t, g;
        
        // case 1: linear dag
        if (is_linear) {
            dijkstra1();

            t = dist1[1][n];
            g = gsum[1][n];
        }
        // case 2: nonlinear dag
        else {
            t = dist[n];
            g = case2(1);
        }

        cout << "Game #" << tt << ": Suckzoo ends game in time " << t << ", earning " << g << " garnet(s).\n";
    }
}
