#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int INF = 1e9 + 7;

int N, M, K;
struct Edge { int w, v; };
vector<Edge> adj[3030];
vector<int> st_node;

void input() {
    cin >> N >> M >> K;
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
    st_node.resize(K);
    for (auto& i : st_node) cin >> i;
}

vector<int> dist;
struct State {
    int w, v;
    bool operator<(const State& rhs) const {
        return w > rhs.w;
    }
};

void dijkstra() {
    dist.resize(N + 1, INF);

    priority_queue<State> pq;
    for (auto& v : st_node) {
        dist[v] = 0;
        pq.push({ dist[v], v });
    }
    
    while (!pq.empty()) {
        auto [w, v] = pq.top();
        pq.pop();

        if (dist[v] < w) continue;

        for (auto& i : adj[v]) {
            if (dist[i.v] <= w + i.w) continue;
            dist[i.v] = w + i.w;
            pq.push({ dist[i.v], i.v });
        }
    }
}

double get_ans() {
    double ret = 0;
    for (int v = 1; v <= N; v++) {
        ret = max(ret, (double)dist[v]);
        for (auto& i : adj[v]) {
            if (dist[v] + i.w <= dist[i.v]) continue;
            if (dist[v] > dist[i.v]) continue;
            ret = max(ret, (double)(dist[v] + i.w + dist[i.v]) / 2);
        }
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

    input();

    dijkstra();

    cout << fixed;
    cout.precision(0);

    cout << (get_ans() + 1e-8);
}