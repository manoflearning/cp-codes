#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
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

// what: LCA via binary lifting for rooted tree.
// time: build O(n log n), query O(log n); memory: O(n log n)
// constraint: 1-indexed tree.
// usage: lca_sparse l; l.init(n); l.add_edge(u,v); l.build(1); int w=l.lca(u,v);
struct lca_sparse {
    int n, lg;
    vector<vector<int>> adj, up;
    vector<int> dep;
 
    void init(int n_) {
        n = n_;
        lg = 1;
        while ((1 << lg) <= n) lg++;
        adj.assign(n + 1, {});
        up.assign(lg, vector<int>(n + 1, 0));
        dep.assign(n + 1, 0);
    }
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs(int v, int p) {
        // goal: set parent and depth.
        up[0][v] = p;
        dep[v] = dep[p] + 1;
        for (int to : adj[v])
            if (to != p) dfs(to, v);
    }
    void build(int root = 1) {
        dfs(root, 0);
        for (int k = 0; k + 1 < lg; k++)
            for (int v = 1; v <= n; v++)
                up[k + 1][v] = up[k][up[k][v]];
    }
    int lca(int a, int b) const {
        if (dep[a] < dep[b]) swap(a, b);
        int diff = dep[a] - dep[b];
        for (int k = 0; k < lg; k++)
            if (diff & (1 << k)) a = up[k][a];
        if (a == b) return a;
        for (int k = lg - 1; k >= 0; k--) {
            if (up[k][a] != up[k][b]) {
                a = up[k][a];
                b = up[k][b];
            }
        }
        return up[0][a];
    }
    int dist(int a, int b) const {
        int lc = lca(a, b);
        return dep[a] + dep[b] - 2 * dep[lc];
    }
};
 
int n;
vector<vector<int>> t;
vector<int> ans;
vector<bool> vis;
lca_sparse lca;

void dfs(int v, int prv, int dist, int &opt, int &opt_dist) {
    if (opt_dist < dist) {
        opt = v;
        opt_dist = dist;
    }

    for (auto &i : t[v]) {
        if (i != prv) dfs(i, v, dist + 1, opt, opt_dist);
    }
}

void f(int v, int prv, bool always) {
    if (!vis[v] && (ans.empty() || lca.dist(ans.back(), v) == 2)) {
        ans.push_back(v);
        vis[v] = 1;
    }

    if (!vis[v] && always) {
        ans.push_back(v);
        vis[v] = 1;
    }

    sort(all(t[v]), [&](int i, int j) {
        return sz(t[i]) < sz(t[j]);
    });

    for (auto &i : t[v]) {
        if (i == prv) continue;
        f(i, v, always);
    }
}

bool is_valid() {
    if (sz(ans) != n) return 0;
    // for (auto &i : ans) cout << i << ' ';
    // cout << '\n';
    for (int i = 0; i < sz(ans); i++) {
        if (lca.dist(ans[i], ans[(i + 1) % n]) > 2) {
            return 0;
        }
    }
    set<int> vis;
    for (auto &i : ans) vis.insert(i);
    return sz(vis) == n;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    t.assign(n + 1, vector<int>());
    lca.init(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        t[u].push_back(v);
        t[v].push_back(u);
        lca.add_edge(u, v);
    }
    vis.assign(n + 1, 0);
    lca.build(1);

    int v1 = -1, v2 = -1;
    int d1 = -1, d2 = -1;
    dfs(1, 0, 0, v1, d1);
    dfs(v1, 0, 0, v2, d2);

    f(v1, 0, 0);
    f(v2, 0, 1);

    bool yes = is_valid();
    if (yes) {
        cout << "Yes\n";
        for (auto &i : ans)
            cout << i << ' ';
        cout << '\n';
    } else {
        cout << "No\n";
    }
}
