#include <bits/stdc++.h>
using namespace std;

const int MAXN = 101010;
const int INF = 1e9 + 7;
const int MAXD = 16;

int n;
vector<int> adj[MAXN];

int par[MAXN][MAXD + 1];
int dep[MAXN];

int siz[MAXN];
int cdpar[MAXN];
bool used[MAXN];

int optd[MAXN], optv[MAXN];

int ans[MAXN];

void input() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void dfs(int v, int prv) {
    par[v][0] = prv;
    dep[v] = 1 + dep[prv];
    for (auto& i : adj[v])
        if (i != prv) dfs(i, v);
}

void sparse_table() {
    for (int i = 0; i < MAXD; i++) {
        for (int v = 1; v <= n; v++) {
            par[v][i + 1] = par[par[v][i]][i];
        }
    }
}
int dist(int u, int v) {
    int ret = 0;

    if (dep[u] > dep[v]) swap(u, v);
    int diff = dep[v] - dep[u];
    for (int i = 0; i <= MAXD; i++) {
        if (diff & (1 << i)) {
            v = par[v][i];
        }
    }
    ret += diff;
    if (u == v) return ret;

    for (int i = MAXD; i >= 0; i--) {
        if (par[u][i] ^ par[v][i]) {
            u = par[u][i];
            v = par[v][i];
            ret += (1 << (i + 1));
        }
    }
    return ret += 2;
}

int get_size(int v, int prv) {
    siz[v] = 1;
    for (auto& i : adj[v]) {
        if (i == prv || used[i]) continue;
        siz[v] += get_size(i, v);
    }
    return siz[v];
}
int get_cent(int v, int prv, int tot) {
    for (auto& i : adj[v]) {
        if (i == prv || used[i]) continue;
        if (siz[i] > tot / 2) return get_cent(i, v, tot);
    }
    return v;
}

void cd(int v, int prv) {
    int tot = get_size(v, prv);
    int cent = get_cent(v, prv, tot);

    cdpar[cent] = prv;

    used[cent] = 1;
    for (auto& i : adj[cent]) {
        if (!used[i]) cd(i, cent);
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

    cd(1, 0);

    dfs(1, 0);

    sparse_table();

    for (int i = 0; i < MAXN; i++) {
        optd[i] = optv[i] = INF;
    }

    for (int v = n; v >= 1; v--) {
        int ansd = INF, ansv = v;
        for (int p = v; p != 0; p = cdpar[p]) {
            int dist_vp = dist(v, p);

            int resd = dist_vp + optd[p];
            int resv = optv[p];

            if (resd < ansd || (resd == ansd && resv < ansv)) {
                ansd = resd;
                ansv = resv;
            }

            if (dist_vp < optd[p] || (dist_vp == optd[p] && v < optv[p])) {
                optd[p] = dist_vp;
                optv[p] = v;
            }
        }

        ans[v] = ansv;
    }

    for (int i = 1; i <= n; i++)
        cout << ans[i] << ' ';
}
