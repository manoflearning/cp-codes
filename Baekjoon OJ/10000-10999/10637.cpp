#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXV = 101010;
const int MAXD = 16;

vector<int> p(MAXV, -1);

int find(int x) {
    if (p[x] < 0) return x;
    return p[x] = find(p[x]);
}

void merge(int a, int b) {
    int A = find(a), B = find(b);
    if (A == B) return;
    p[B] += p[A];
    p[A] = B;
}

struct wv { ll w; int v; };
struct wuv { 
    ll w; int u, v, idx;
    bool operator<(const wuv& rhs) const {
        return w < rhs.w;
    }
};

int n, m, edgeVisited[MAXV << 1];
vector<wv> adj[MAXV], t[MAXV];
vector<wuv> e;
ll wSum = 0;

void input() {
    cin >> n >> m;
    e.resize(m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
        e[i] = { w, u, v, i };
    }
}

void buildMST() {
    vector<wuv> e2 = e;
    sort(e2.begin(), e2.end());
    for (auto& i : e2) {
        if (find(i.u) == find(i.v)) continue;
        
        merge(i.u, i.v);
        edgeVisited[i.idx] = 1;
        wSum += i.w;

        t[i.u].push_back({ i.w, i.v });
        t[i.v].push_back({ i.w, i.u });
    }
}

int vi[MAXV], par[MAXV][MAXD + 1], dep[MAXV];
ll w[MAXV][MAXD + 1];

void dfs(int v) {
    vi[v] = 1;
    for (auto& i : t[v]) {
        if (vi[i.v]) continue;
        par[i.v][0] = v;
        dep[i.v] = dep[v] + 1;
        w[i.v][0] = i.w;
        dfs(i.v);
    }
}

void buildSparseTable() {
    for (int i = 1; i <= MAXD; i++) {
        for (int v = 1; v <= n; v++) {
            par[v][i] = par[par[v][i - 1]][i - 1];
            w[v][i] = max(w[v][i - 1], w[par[v][i - 1]][i - 1]);
        }
    }
}

ll lca(int u, int v) {
    ll ret = 0;

    if (dep[u] < dep[v]) swap(u, v);

    int diff = dep[u] - dep[v];
    for (int i = MAXD; i >= 0; i--) {
        if (diff & (1 << i)) {
            ret = max(ret, w[u][i]);
            u = par[u][i];
        }
    }

    if (u == v) return ret;

    for (int i = MAXD; i >= 0; i--) {
        if (par[u][i] ^ par[v][i]) {
            ret = max({ ret, w[u][i], w[v][i] });
            u = par[u][i];
            v = par[v][i];
        }
    }

    return max({ ret, w[u][0], w[v][0] });
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    buildMST();
    
    for (int v = 1; v <= n; v++) {
        if (!vi[v]) dfs(v);
    }

    buildSparseTable();

    for (auto& i : e) {
        if (edgeVisited[i.idx]) {
            
            cout << wSum - i.w - lca(i.u, i.v) << '\n';
        }
        else cout << wSum << '\n';
    }

    return 0;
}