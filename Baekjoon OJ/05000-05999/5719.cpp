// 1. dijkstra
// 2. build dijkstra dag
// 3. run dijkstra one more time, avoid every edges in the dijkstra dag

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;

int n, m;
int st, en;
struct Edge {
    int v, w, idx;
};
vector<Edge> adj[505], radj[505];
int dist[505];
bool banned[10101];

void init() {
    for (int v = 0; v < 505; v++) {
        adj[v].clear();
        radj[v].clear();
    }
    memset(banned, 0, sizeof(banned));
}

void input() {
    cin >> n >> m;
    if (n == 0 && m == 0) exit(0);
    cin >> st >> en;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ v, w, i + 1 });
        radj[v].push_back({ u, w, i + 1 });
    }
}

struct State {
    int v, w;
    bool operator<(const State& rhs) const {
        return w > rhs.w;
    }
};
void dijkstra() {
    for (int v = 0; v < n; v++) dist[v] = INF;
    dist[st] = 0;
    priority_queue<State> pq;
    pq.push({ st, dist[st] });

    while (!pq.empty()) {
        auto [v, w] = pq.top();
        pq.pop();
        if (dist[v] < w) continue;
        for (auto& i : adj[v]) {
            if (w + i.w < dist[i.v] && !banned[i.idx]) {
                dist[i.v] = w + i.w;
                pq.push({ i.v, dist[i.v] });
            }
        }
    }
}

void buildDijkstraDag() {
    vector<bool> vi(n);
    queue<pii> qu;
    qu.push({ en, dist[en] });
    vi[en] = true;

    while (!qu.empty()) {
        auto [v, w] = qu.front();
        qu.pop();

        for (auto& i : radj[v]) {
            if (dist[i.v] + i.w == w) {
                banned[i.idx] = true;
                if (!vi[i.v]) {
                    qu.push({ i.v, dist[i.v] });
                    vi[i.v] = true;
                }
            }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    while (1) {
        init();

        input();

        dijkstra();

        buildDijkstraDag();

        dijkstra();

        cout << (dist[en] == INF ? -1 : dist[en]) << '\n';
    }
}