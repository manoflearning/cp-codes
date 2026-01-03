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

constexpr int N = 121;

// dinic max flow (0-based).
// what: compute maximum flow in a directed graph (Dinic).
// time: O(E V^2) worst; memory: O(E)
// constraint: cap >= 0
// usage: dinic mf(n); mf.add_edge(u, v, cap); ll f = mf.max_flow(s, t);
struct dinic {
    static constexpr ll INF = (1LL << 62);

    struct edge {
        int to, rev;
        ll cap;
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
        g.assign(n, {});
    }

    edge_ref add_edge(int u, int v, ll cap) {
        // goal: add forward + reverse edge
        edge a{v, (int)g[v].size(), cap};
        edge b{u, (int)g[u].size(), 0};
        g[u].push_back(a);
        g[v].push_back(b);
        return {u, (int)g[u].size() - 1};
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
        level.assign(n, -1);
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

    ll dfs(int v, int t, ll f) {
        if (v == t || f == 0) return f;
        for (int &i = work[v]; i < (int)g[v].size(); i++) {
            edge &e = g[v][i];
            if (e.cap == 0 || level[e.to] != level[v] + 1) continue;
            // invariant: level strictly increases along augmenting path
            ll pushed = dfs(e.to, t, min(f, e.cap));
            if (pushed == 0) continue;
            e.cap -= pushed;
            g[e.to][e.rev].cap += pushed;
            return pushed;
        }
        return 0;
    }

    ll max_flow(int s, int t, ll limit = INF) {
        if (s == t) return 0; // edge: no flow needed
        ll flow = 0;
        while (flow < limit && bfs(s, t)) {
            work.assign(n, 0);
            while (flow < limit) {
                ll pushed = dfs(s, t, limit - flow);
                if (pushed == 0) break;
                flow += pushed;
            }
        }
        return flow;
    }
};

int n;
vector<string> s[N][3];
vector<int> a[N][3];

void init() {
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            s[i][j].clear();
            a[i][j].clear();
        }
    }
}

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            int m; cin >> m;
            s[i][j].resize(m);
            for (auto &t : s[i][j]) cin >> t;
        }
    }
}

void coor_comp() {
    vector<string> cc;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            for (auto &t : s[i][j]) {
                cc.push_back(t);
            }
        }
    }

    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());
    
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 3; j++) {
            for (auto &t : s[i][j]) {
                int x = lower_bound(all(cc), t) - cc.begin() + 1;
                a[i][j].push_back(x);
            }
        }
    }
}

bool f(int mid) {
    const int n_nodes = 3 * 10 * n + 4 * n + 2;

    dinic flow{n_nodes};

    const int s = 0;
    const int e = 3 * 10 * n + 4 * n + 1;

    for (int i = 1; i <= 3 * 10 * n; i++) {
        flow.add_edge(s, i, 2);
    }

    for (int i = 1; i <= mid; i++) {
        for (int j = 0; j < 3; j++) {
            for (auto &t : a[i][j]) {
                const int x = t;
                const int y = 3 * 10 * n + (i - 1) * 4 + j + 1;
                flow.add_edge(x, y, 1);
            }
        }
    }

    for (int i = 1; i <= mid; i++) {
        const int y = 3 * 10 * n + (i - 1) * 4 + 3 + 1;
        for (int j = 0; j < 3; j++) {
            const int x = 3 * 10 * n + (i - 1) * 4 + j + 1;
            flow.add_edge(x, y, 1);
        }
        flow.add_edge(y, e, 3);
    }

    ll res = flow.max_flow(s, e);
    return res == 3 * mid;
}

int solve() { // TC: O(log n * )
    int l = 0, r = n;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (f(mid)) l = mid;
        else r = mid - 1;
    }
    return l;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        coor_comp();

        cout << solve() << '\n';
    }
}
