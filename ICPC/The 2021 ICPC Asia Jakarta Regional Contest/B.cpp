#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 101010;
const int INF = 1e9 + 7;

vector<int> uf(MAXN, -1);
int find(int x) {
    if (uf[x] < 0) return x;
    return uf[x] = find(uf[x]);
}
void merge(int u, int v) {
    int U = find(u), V = find(v);
    if (U == V) return;
    uf[U] = V;
}

int flag;
struct Seg {
    vector<int> t, lazy;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1, INF);
        lazy.resize(flag << 1, INF);
    }
    void modify(int l, int r, int val, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            lazy[n] = val;
            propagate(n);
            return;
        }
        int mid = (nl + nr) >> 1;
        modify(l, r, val, n << 1, nl, mid);
        modify(l, r, val, n << 1 | 1, mid + 1, nr);
        t[n] = min(t[n << 1], t[n << 1 | 1]);
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);

        if (r < nl || nr < l) return INF;
        if (l <= nl && nr <= r) return t[n];
        
        int mid = (nl + nr) >> 1;
        return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
    void propagate(int n) {
        if (n < flag) {
            lazy[n << 1] = min(lazy[n << 1], lazy[n]);
            lazy[n << 1 | 1] = min(lazy[n << 1 | 1], lazy[n]);
        }
        t[n] = min(t[n], lazy[n]);
        lazy[n] = INF;
    }
}seg;

int n, m, a[MAXN];
struct Edge { int u, v, w; };
vector<Edge> e, rem;
vector<int> adj[MAXN], g[MAXN];

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    e.resize(m);
    for (auto& i : e) {
        cin >> i.u >> i.v;
        i.w = abs(a[i.u] - a[i.v]);
    }
}

void mst() {
    sort(e.begin(), e.end(), [&](const Edge& e1, const Edge& e2) {
        return e1.w < e2.w;
    });

    for (auto& i : e) {
        if (find(i.u) == find(i.v)) {
            rem.push_back(i);
            continue;
        }
        merge(i.u, i.v);
        adj[i.u].push_back(i.v);
        adj[i.v].push_back(i.u);
    }
}

void dfs(int v, int prv) {
    for (auto& i : adj[v]) {
        if (i == prv) continue;
        g[v].push_back(i);
        dfs(i, v);
    }
}

int siz[MAXN], dep[MAXN], par[MAXN];
int top[MAXN], in[MAXN], out[MAXN], pv;

int dfs1(int v) {
    siz[v] = 1;
    for (auto& i : g[v]) {
        dep[i] = dep[v] + 1, par[i] = v;
        siz[v] += dfs1(i);
        if (siz[i] > siz[g[v][0]]) swap(i, g[v][0]);
    }
    return siz[v];
}

void dfs2(int v) {
    in[v] = ++pv;
    for (auto& i : g[v]) {
        top[i] = (i == g[v][0] ? top[v] : i);
        dfs2(i);
    }
    out[v] = pv;
}

void modify(int u, int v, int w) {
    while (top[u] ^ top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        int st = top[u];
        seg.modify(in[st], in[u], w);
        u = par[st];
    }
    if (dep[u] > dep[v]) swap(u, v);
    seg.modify(in[u], in[v], w);
}

int query(int v) {
    return seg.query(in[v], in[v]);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    mst();

    dfs(1, 0);
    top[1] = 1;
    dfs1(1);
    dfs2(1);

    seg.build(n);

    for (auto& i : rem) {
        modify(i.u, i.v, i.w);
    }

    for (int v = 1; v <= n; v++) {
        int res = query(v);
        cout << (res == INF ? -1 : res) << ' ';
    }
}