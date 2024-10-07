#include <bits/stdc++.h>
using namespace std;

const int MAXN = 101010;
const int MAXD = 16 + 1;
const int MAXM = 101010;
const int SQ = 373;

int n, a[MAXN];
vector<int> adj[MAXN];

int m;
struct Query {
    int u, v, s, e, lca;
    int idx;
    bool operator<(const Query& rhs) const {
        if (s / SQ != rhs.s / SQ) return s / SQ < rhs.s / SQ;
        else return (s / SQ) & 1 ? e < rhs.e : e > rhs.e;
    }
};
Query q[MAXM];
int ans[MAXM];

int in[MAXN], out[MAXN], arr[MAXN << 1], p;
int dep[MAXN];
int par[MAXN][MAXD];

int cntv[MAXN], cntw[1010101], res;

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
        cin >> q[i].u >> q[i].v;
        q[i].idx = i;
    }
}

void dfs(int v, int prv) {
    dep[v] = 1 + dep[prv];
    par[v][0] = prv;

    in[v] = ++p;
    arr[in[v]] = v;
    for (auto& i : adj[v])
        if (i != prv) dfs(i, v);
    out[v] = ++p;
    arr[out[v]] = v;
}

bool is_anc(int u, int v) {
    return in[v] <= in[u] && out[u] <= out[v];
}

void build_sparse_table() {
    for (int d = 1; d < MAXD; d++) {
        for (int v = 1; v <= n; v++) {
            par[v][d] = par[par[v][d - 1]][d - 1];
        }
    }
}

int lca(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    int diff = dep[v] - dep[u];
    for (int d = 0; d < MAXD; d++) {
        if (diff & (1 << d)) v = par[v][d];
    }
    if (u == v) return v;
    for (int d = MAXD - 1; d >= 0; d--) {
        if (par[u][d] ^ par[v][d]) {
            u = par[u][d];
            v = par[v][d];
        }
    }
    return par[u][0];
}

void add(int w) {
    cntw[w]++;
    if (cntw[w] == 1) res++;
}
void del(int w) {
    cntw[w]--;
    if (cntw[w] == 0) res--;
}
void modify(int v, int val) {
    cntv[v] += val;
    // cout << v << ' ' << cntv[v] << '\n';
    assert(0 <= cntv[v] && cntv[v] <= 2);
    if (cntv[v] & 1) add(a[v]);
    else del(a[v]);
}

void mo() {
    int s = q[1].s, e = q[1].e;
    for (int i = s; i <= e; i++) {
        modify(arr[i], 1);
    }
    if (q[1].lca != -1) add(a[q[1].lca]);
    ans[q[1].idx] = res;

    for (int i = 2; i <= m; i++) {
        if (q[i].lca != -1) add(a[q[i].lca]);
        if (q[i - 1].lca != -1) del(a[q[i - 1].lca]);

        while (q[i].s < s) modify(arr[--s], 1);
        while (e < q[i].e) modify(arr[++e], 1);
        while (s < q[i].s) modify(arr[s++], -1);
        while (q[i].e < e) modify(arr[e--], -1);

        ans[q[i].idx] = res;
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

    for (int i = 1; i <= m; i++) {
        auto& it = q[i];
        if (in[it.u] > in[it.v]) swap(it.u, it.v);

        if (is_anc(it.v, it.u)) {
            it.s = in[it.u];
            it.e = in[it.v];
            it.lca = -1;
        } else {
            it.s = out[it.u];
            it.e = in[it.v];
            it.lca = lca(it.u, it.v);
        }
    }

    sort(q + 1, q + m + 1);

    mo();

    for (int i = 1; i <= m; i++)
        cout << ans[i] << '\n';
}
