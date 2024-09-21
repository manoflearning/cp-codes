#include <bits/stdc++.h>
using namespace std;

const int MAXN = 101010;
const int MAXD = 16;

int n, q, rt;
vector<vector<int>> adj(MAXN);
vector<vector<int>> par(MAXN, vector<int>(MAXD + 1));
vector<int> dep(MAXN), siz(MAXN);

void init() {
    for (int i = 0; i < MAXN; i++) {
        adj[i].clear();
    }
}

void input() {
    cin >> n >> q >> rt;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void dfs(int v, int prv) {
    par[v][0] = prv;
    dep[v] = dep[prv] + 1;
    siz[v] = 1;
    for (auto& i : adj[v]) {
        if (i == prv) continue;
        dfs(i, v);
        siz[v] += siz[i];
    }
}

void build_sparse_table() {
    for (int d = 1; d <= MAXD; d++) {
        for (int i = 1; i <= n; i++) {
            par[i][d] = par[par[i][d - 1]][d - 1];
        }
    }
}

int lca(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);

    int diff = dep[v] - dep[u];
    for (int d = MAXD; d >= 0; d--) {
        if (diff & (1 << d)) v = par[v][d];
    }

    if (u == v) return u;

    for (int d = MAXD; d >= 0; d--) {
        if (par[u][d] ^ par[v][d]) {
            u = par[u][d];
            v = par[v][d];
        }
    }

    return par[u][0];
}

int goup(int v, int len) {
    for (int d = MAXD; d >= 0; d--) {
        if (len & (1 << d)) v = par[v][d];
    }
    return v;
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
        cout << "Case #" << tt << ":\n";

        init();

        input();

        dfs(2, 0);

        build_sparse_table();

        while (q--) {
            int op, v;
            cin >> op >> v;
            if (op == 0) rt = v;
            if (op == 1) {
                if (v == rt) cout << n << '\n';
                else if (lca(v, rt) == v) {
                    int chd = goup(rt, dep[rt] - dep[v] - 1);
                    cout << n - siz[chd] << '\n';
                } else {
                    cout << siz[v] << '\n';
                }
            }
        }
    }
}
