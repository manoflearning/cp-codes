#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const int MAXN = 101010;
const int INF = 1e9 + 7;

int n;
vector<pii> adj[101010];

int dep[101010];
int par[101010][17], dist[101010][17];

int siz[101010], cdpar[101010];
bool used[101010];

bool is_w[101010];
int cddist[101010][17];

unordered_map<int, multiset<int>> sub[101010];
multiset<int> st[101010], ans;

void input() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
}

void dfs(int v, int prv) {
    dep[v] = 1 + dep[prv];
    par[v][0] = prv;
    for (auto& [w, u] : adj[v]) {
        if (u == prv) continue;
        dist[u][0] = w;
        dfs(u, v);
    }
}
void build_sparse_table() {
    for (int d = 0; d + 1 <= 16; d++) {
        for (int v = 1; v <= n; v++) {
            par[v][d + 1] = par[par[v][d]][d];
            dist[v][d + 1] = dist[v][d] + dist[par[v][d]][d];
        }
    }
}
int get_dist(int u, int v) {
    int ret = 0;
    if (dep[u] > dep[v]) swap(u, v);
    int diff = dep[v] - dep[u];
    for (int i = 0; i <= 16; i++) {
        if ((1 << i) & diff) {
            ret += dist[v][i];
            v = par[v][i];
        }
    }
    if (u == v) return ret;
    for (int i = 16; i >= 0; i--) {
        if (par[u][i] ^ par[v][i]) {
            ret += dist[u][i];
            ret += dist[v][i];
            u = par[u][i];
            v = par[v][i];
        }
    }
    return ret + dist[u][0] + dist[v][0];
}

int get_size(int v, int prv) {
    siz[v] = 1;
    for (auto& [_, u] : adj[v]) {
        if (used[u] || u == prv) continue;
        siz[v] += get_size(u, v);
    }
    return siz[v];
}
int get_cent(int v, int prv, int mxsiz) {
    for (auto& [_, u] : adj[v]) {
        if (used[u] || u == prv) continue;
        if (siz[u] > mxsiz / 2) return get_cent(u, v, mxsiz);
    }
    return v;
}
void cd(int v, int prv) {
    int mxsiz = get_size(v, prv);
    int cent = get_cent(v, prv, mxsiz);

    cdpar[cent] = prv;
    used[cent] = 1;

    for (auto& [_, u] : adj[cent]) {
        if (!used[u]) cd(u, cent);
    }
}

void add_ans(int v) {
    if (sz(st[v]) == 1) ans.insert(0);
    else if (sz(st[v]) >= 2) {
        auto it = st[v].end();
        int p = *(--it), q = *(--it);
        ans.insert(p + q);
    }
}
void del_ans(int v) {
    if (sz(st[v]) == 1) ans.erase(ans.find(0));
    else if (sz(st[v]) >= 2) {
        auto it = st[v].end();
        int p = *(--it), q = *(--it);
        ans.erase(ans.find(p + q));
    }
}

void add(int v, int prv, int w) {
    auto& tmp = sub[v][prv];
    if (tmp.empty() || *tmp.rbegin() < w) {
        del_ans(v);
        if (!tmp.empty())
            st[v].erase(st[v].find(*tmp.rbegin()));
        st[v].insert(w);
        add_ans(v);
    }
    tmp.insert(w);
}
void del(int v, int prv, int w) {
    auto& tmp = sub[v][prv];
    tmp.erase(tmp.find(w));
    if (tmp.empty() || *tmp.rbegin() < w) {
        del_ans(v);
        st[v].erase(st[v].find(w));
        if (!tmp.empty())
            st[v].insert(*tmp.rbegin());
        add_ans(v);
    }
}

void build_cdtree() {
    for (int v = 1; v <= n; v++) {
        is_w[v] = 1;
        int prv = 0;
        for (int p = v, i = 0; p != 0; p = cdpar[p], i++) {
            cddist[v][i] = get_dist(p, v);
            add(p, prv, cddist[v][i]);
            prv = p;
        }
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

    cd(1, 0);
    build_cdtree();

    int q; cin >> q;
    while (q--) {
        int op; cin >> op;

        if (op == 1) {
            int v; cin >> v;
            is_w[v] = !is_w[v];
            int prv = 0;
            for (int p = v, i = 0; p != 0; p = cdpar[p], i++) {
                if (is_w[v]) add(p, prv, cddist[v][i]);
                else del(p, prv, cddist[v][i]);
                prv = p;
            }
        }
        if (op == 2) {
            cout << (ans.empty() ? -1 : max(0, *ans.rbegin())) << '\n';
        }
    }
}
