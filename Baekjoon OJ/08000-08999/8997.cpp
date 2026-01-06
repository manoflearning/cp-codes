#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

// what: compute maximum flow in a directed graph (Dinic).
// time: O(E V^2) worst; memory: O(E)
// constraint: 1-indexed [1..n]; cap >= 0.
// usage: dinic mf(n); mf.add_edge(u, v, cap); ll f = mf.max_flow(s, t);
struct dinic {
    static constexpr int INF = 1e9 + 7;

    struct edge {
        int to, rev, cap;
    };
    struct edge_ref {
        int u, idx;
    };

    int n;
    vector<vector<edge>> g;
    vector<int> level, work;

    dinic(int n = 0) { init(n); }
    void init(int n_) {
        n = n_;
        g.assign(n + 1, {});
    }
    edge_ref add_edge(int u, int v, int cap) {
        // goal: add forward + reverse edge
        edge a{v, sz(g[v]), cap};
        edge b{u, sz(g[u]), 0};
        g[u].push_back(a);
        g[v].push_back(b);
        return {u, sz(g[u]) - 1};
    }
    ll edge_flow(edge_ref e) const {
        // goal: current flow on original edge
        const edge &ed = g[e.u][e.idx];
        return g[ed.to][ed.rev].cap;
    }
    void clear_edge(edge_ref e) {
        // goal: remove edge from residual graph
        edge &ed = g[e.u][e.idx];
        edge &rev = g[ed.to][ed.rev];
        ed.cap = 0;
        rev.cap = 0;
    }

    bool bfs(int s, int t) {
        // goal: build level graph
        level.assign(n + 1, -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (const auto &e : g[v]) {
                if (e.cap == 0 || level[e.to] != -1) continue;
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
        return level[t] != -1;
    }
    int dfs(int v, int t, int f) {
        if (v == t || f == 0) return f;
        for (int &i = work[v]; i < sz(g[v]); i++) {
            edge &e = g[v][i];
            if (e.cap == 0 || level[e.to] != level[v] + 1) continue;
            // invariant: level strictly increases along augmenting path
            int pushed = dfs(e.to, t, min(f, e.cap));
            if (pushed == 0) continue;
            e.cap -= pushed;
            g[e.to][e.rev].cap += pushed;
            return pushed;
        }
        return 0;
    }
    int max_flow(int s, int t, int limit = INF) {
        if (s == t) return 0; // edge: no flow needed
        int flow = 0;
        while (flow < limit && bfs(s, t)) {
            work.assign(n + 1, 0);
            while (flow < limit) {
                int pushed = dfs(s, t, limit - flow);
                if (pushed == 0) break;
                flow += pushed;
            }
        }
        return flow;
    }
};

int n;
vector<int> w, d;
vector<vector<int>> a;

void init() {
    w.clear();
    d.clear();
    a.clear();
}

void input() {
    cin >> n;
    w.resize(n);
    d.resize(n);
    a.resize(n, vector<int>(n));

    for (int i = 0; i < n; i++)
        cin >> w[i] >> d[i];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) cin >> a[i][j];
}

vector<int> solve() {
    vector<int> ret;

    const int st = n + n * n + 1;
    const int en = n + n * n + 2;
    for (int i = 0; i < n; i++) {
        dinic mf(n + n * n + 2);

        ll ub = w[i];

        ll tgt = 0;
        for (int y = 0; y < n; y++) {
            for (int x = y + 1; x < n; x++) {    
                if (a[y][x] == 0) continue;

                if (y == i || x == i) {
                    ub += a[y][x];
                } else {
                    const int u = y + 1;
                    const int v = x + 1;
                    const int p = n + 1 + n * y + x;

                    mf.add_edge(st, p, a[y][x]);
                    mf.add_edge(p, u, a[y][x]);
                    mf.add_edge(p, v, a[y][x]);

                    tgt += a[y][x];
                }
            }
        }

        for (int v = 0; v < n; v++) {
            if (v != i) {
                if (w[v]) mf.add_edge(st, v + 1, w[v]);
                mf.add_edge(v + 1, en, ub);
                tgt += w[v];
            }
        }

        ll res = mf.max_flow(st, en);
        if (res == tgt) ret.push_back(i);
    }

    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        auto ans = solve();
        for (auto &i : ans) cout << i + 1 << ' ';
        cout << '\n';
    }
}
