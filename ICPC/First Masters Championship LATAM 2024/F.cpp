#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAXD = 20;

int n;
vector<int> adj[202020];
int dep[202020], par[202020][MAXD + 1];

void input() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void dfs(int now, int prv) {
    par[now][0] = prv;
    dep[now] = dep[prv] + 1;
    for (auto& i : adj[now]) {
        if (i == prv) continue;
        dfs(i, now);
    }
}

void build_sparse_table() {
    for (int i = 1; i <= MAXD; i++) {
        for (int v = 1; v <= n; v++) {
            par[v][i] = par[par[v][i - 1]][i - 1];
        }
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int diff = dep[u] - dep[v];
    for (int i = MAXD; i >= 0; i--)
        if (diff & (1 << i)) u = par[u][i];
    if (u == v) return u;
    for (int i = MAXD; i >= 0; i--) {
        if (par[u][i] ^ par[v][i]) {
            u = par[u][i];
            v = par[v][i];
        }
    }
    return par[u][0];
}

int dist(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int ret = 0;
    int diff = dep[u] - dep[v];
    ret += diff;
    for (int i = MAXD; i >= 0; i--)
        if (diff & (1 << i)) u = par[u][i];
    if (u == v) return ret;
    for (int i = MAXD; i >= 0; i--) {
        if (par[u][i] ^ par[v][i]) {
            ret += 2 * (1 << i);
            u = par[u][i];
            v = par[v][i];
        }
    }
    ret += 2;
    return ret;
}

int goup(int u, int d) {
    for (int i = MAXD; i >= 0; i--)
        if (d & (1 << i)) u = par[u][i];
    return u;
}

pair<int, int> mid_nodes(int u, int v) {
    int lc = lca(u, v);

    int d_u = dist(u, lc), d_v = dist(v, lc);

    if (d_u < d_v) {
        swap(d_u, d_v);
        swap(u, v);
    }

    int diff = d_u - (d_u - d_v) / 2;

    // cout << u << ' ' << v << ' ' << lc << '\n';
    // cout << dist(u, lc) << ' ' << dist(v, lc) << '\n';

    if ((d_u - d_v) % 2 == 0) {
        return { goup(u, diff), -1 };
    }
    else {
        int p = goup(u, diff - 1);
        int q = goup(p, 1);
        return { p, q };
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

    dfs(1, 0);

    build_sparse_table();

    int q; cin >> q;
    while (q--) {
        int a, b, c;
        cin >> a >> b >> c;

        auto [mab1, mab2] = mid_nodes(a, b);
        auto [mbc1, mbc2] = mid_nodes(b, c);
        auto [mac1, mac2] = mid_nodes(a, c);

        vector<int> mids = { mab1, mab2, mbc1, mbc2, mac1, mac2 };

        int ans = 1e9;
        for (auto& v : mids) {
            if (v == -1) continue;
            // cout << v << ' ';
            ans = min(ans, max({ dist(v, a), dist(v, b), dist(v, c) }));
        }
        // cout << '\n';

        cout << ans << '\n';
    }
}