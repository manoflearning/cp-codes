#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pli = pair<ll, int>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr ll INF = 1e18;

int n, m;
vector<int> c;
vector<vector<int>> a;
vector<vector<pli>> adj;

void init() {
    c.clear();
    a.clear();
    adj.clear();
}

void input() {
    cin >> n >> m;
    
    c.resize(n);
    for (int i = 0; i < n; i++) cin >> c[i];
    a.resize(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
}

int _hash(int i, int j, bool is_y) {
    int ret = 0;
    ret += n;
    ret += ((m * i + j) << 1) | is_y;
    return ret;
}

void build_graph() {
    adj.resize(n + 2 * n * m);
    for (int j = 0; j < m; j++) {
        vector<int> ord(n);
        iota(all(ord), 0);
        sort(all(ord), [&](int lhs, int rhs) {
            return a[lhs][j] < a[rhs][j];
        });

        for (int k = 0; k + 1 < n; k++) {
            int u = ord[k], v = ord[k + 1];
            adj[_hash(u, j, 0)].push_back({a[v][j] - a[u][j], _hash(v, j, 0)});
            adj[_hash(v, j, 1)].push_back({0, _hash(u, j, 1)});
        }

        for (int k = 0; k < n; k++) {
            int u = ord[k];
            adj[u].push_back({c[u], _hash(u, j, 0)});
            adj[_hash(u, j, 1)].push_back({0, u});
            adj[_hash(u, j, 0)].push_back({0, _hash(u, j, 1)});
        }
    }
}

ll dijkstra() {
    vector<ll> dist(n + 2 * n * m, INF);
    priority_queue<pli, vector<pli>, greater<pli>> pq;

    dist[n - 1] = 0;
    pq.push({0, n - 1});

    while (!pq.empty()) {
        auto [w, v] = pq.top();
        pq.pop();
        // cout << w << ' ' << v << '\n';
        if (dist[v] != w) continue;

        for (auto &i : adj[v]) {
            if (dist[i.sc] <= w + i.fr) continue;
            dist[i.sc] = w + i.fr;
            pq.push({dist[i.sc], i.sc});
        }
    }

    return dist[0];
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        build_graph();
        
        cout << dijkstra() << '\n';
    }
}
