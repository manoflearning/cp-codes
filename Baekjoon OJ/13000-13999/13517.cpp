#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size() 

struct PST {
    int flag;
    struct Node { int l, r, val; };
    vector<Node> t;
    vector<int> root;
    
    void addNode() { t.push_back({ -1, -1, 0 }); };
    void build(int l, int r, int n) {
        if (l == r) return;
        addNode();
        t[n].l = sz(t) - 1;
        addNode();
        t[n].r = sz(t) - 1;

        int mid = (l + r) >> 1;
        build(l, mid, t[n].l);
        build(mid + 1, r, t[n].r);
    }
    void build() {
        flag = 1'000'000;
        root.resize(101010);
        addNode();
        root[0] = sz(t) - 1;
        build(1, flag, root[0]);
    }
    void modify(int p, int l, int r, int n1, int n2) {
        if (p < l || r < p) { t[n2] = t[n1]; return; }
        if (l == r) { t[n2].val = t[n1].val + 1; return; }

        int mid = (l + r) >> 1;
        if (p <= mid) {
            t[n2].r = t[n1].r;
            addNode();
            t[n2].l = sz(t) - 1;
            modify(p, l, mid, t[n1].l, t[n2].l);
        }
        else {
            t[n2].l = t[n1].l;
            addNode();
            t[n2].r = sz(t) - 1;
            modify(p, mid + 1, r, t[n1].r, t[n2].r);
        }
        t[n2].val = t[t[n2].l].val + t[t[n2].r].val;
    }
    void modify(int p, int v1, int v2) {
        addNode();
        root[v2] = sz(t) - 1;
        //assert(v1 == 0 || root[v1] != 0);
        modify(p, 1, flag, root[v1], root[v2]);
    }
    int query(int u, int v, int lca, int lcap, int k, int nl, int nr) {
        if (nl == nr) return nl;
        int mid = (nl + nr) >> 1;
        int res = t[t[u].l].val + t[t[v].l].val - t[t[lca].l].val - t[t[lcap].l].val;
        if (k <= res) return query(t[u].l, t[v].l, t[lca].l, t[lcap].l, k, nl, mid);
        else return query(t[u].r, t[v].r, t[lca].r, t[lcap].r, k - res, mid + 1, nr);
    }
    int query(int u, int v, int lca, int lcap, int k) {
        return query(root[u], root[v], root[lca], root[lcap], k, 1, flag);
    }
} pst;

int n, a[101010];
vector<int> adj[101010];

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

const int MAXD = 16;

int dep[101010], par[101010][MAXD + 1];

void dfs(int now, int prv) {
    par[now][0] = prv;
    dep[now] = dep[prv] + 1;
    for (auto i : adj[now]) {
        if (i != prv) dfs(i, now);
    }
}

void buildSparseTable() {
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

void dfsBuildPST(int v, int prv) {
    pst.modify(a[v], prv, v);
    for (auto& i : adj[v]) {
        if (i != prv) dfsBuildPST(i, v);
    }
}

void buildPST() {
    pst.build();
    dfsBuildPST(1, 0);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    input();

    dfs(1, 0);
    buildSparseTable();

    buildPST();
    
    int q; cin >> q;
    while (q--) {
        int u, v, k;
        cin >> u >> v >> k;
        int lc = lca(u, v);

        /*int all = pst.t[pst.root[u]].val;
        all += pst.t[pst.root[v]].val;
        all -= pst.t[pst.root[lc]].val;
        all -= pst.t[pst.root[par[lc][0]]].val;
        assert(1 <= k && k <= all);*/

        cout << pst.query(u, v, lc, par[lc][0], k) << '\n';
    }
}