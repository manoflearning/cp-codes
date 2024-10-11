#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 303030;
const int MAXK = 5050;
const int MAXD = 18;
const int INF = 1e9 + 7;

int n, K;
vector<int> adj[MAXN];
vector<int> arr;

void input() {
    cin >> n >> K;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    arr.resize(K);
    for (auto& i : arr) cin >> i;
}

int in[MAXN], p;
int dep[MAXN];
int par[MAXN][MAXD + 1];

void dfs(int v, int prv) {
    in[v] = ++p;
    dep[v] = 1 + dep[prv];
    par[v][0] = prv;
    for (auto& i : adj[v]) {
        if (i == prv) continue;
        dfs(i, v);
    }
}

void build_sparse_table() {
    for (int d = 0; d + 1 <= MAXD; d++) {
        for (int v = 1; v <= n; v++) {
            par[v][d + 1] = par[par[v][d]][d];
        }
    }
}

int get_dist(int u, int v) {
    int ret = 0;
    if (dep[u] > dep[v]) swap(u, v);
    int diff = dep[v] - dep[u];
    for (int i = 0; i <= MAXD; i++) {
        if (diff & (1 << i)) v = par[v][i];
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
    return ret + 2;
}
int lca(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    int diff = dep[v] - dep[u];
    for (int i = 0; i <= MAXD; i++) {
        if (diff & (1 << i)) {
            v = par[v][i];
        }
    }
    if (u == v) return u;
    for (int i = MAXD; i >= 0; i--) {
        if (par[u][i] ^ par[v][i]) {
            u = par[u][i];
            v = par[v][i];
        }
    }
    return par[u][0];
}

struct Edge { int w, v; };
vector<Edge> cpchd[MAXN];
bool has[MAXN];

void tree_comp() {
    for (auto& i : arr) has[i] = 1;

    sort(all(arr), [&](int p1, int p2) {
        return in[p1] < in[p2];
    });
    for (int i = 0; i + 1 < K; i++)
        arr.push_back(lca(arr[i], arr[i + 1]));
    sort(all(arr), [&](int p1, int p2) {
        return in[p1] < in[p2];
    });
    arr.erase(unique(all(arr)), arr.end());

    for (int i = 1; i < sz(arr); i++) {
        int v = arr[i];
        int p = lca(arr[i - 1], arr[i]);
        cpchd[p].push_back({ dep[v] - dep[p], v });
    }
}

int tot[MAXN];
vector<int> dp1[MAXN], dp2[MAXN];

void f(int v) {
    if (has[v]) tot[v] = 1;

    dp1[v].resize(2, INF);
    dp2[v].resize(2, INF);

    dp1[v][0] = dp2[v][0] = 0;
    dp1[v][tot[v]] = dp2[v][tot[v]] = 0;

    for (auto [w, u] : cpchd[v]) {
        f(u);

        dp1[v].resize(tot[v] + tot[u] + 1, INF);
        dp2[v].resize(tot[v] + tot[u] + 1, INF);

        for (int x = tot[v] + tot[u]; x >= 1; x--) {
            for (int j = max(1, x - tot[v]); j <= min(x, tot[u]); j++) {
                int i = x - j;
                dp1[v][x] = min(dp1[v][x], dp1[v][i] + dp1[u][j] + 2 * w);

                dp2[v][x] = min(dp2[v][x], dp1[v][i] + dp2[u][j] + w);
                dp2[v][x] = min(dp2[v][x], dp2[v][i] + dp1[u][j] + 2 * w);
            }
        }

        tot[v] += tot[u];
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

    tree_comp();

    f(arr[0]);

    int add = get_dist(arr[0], 1);
    for (int k = 1; k <= K; k++)
        cout << dp2[arr[0]][k] + add << '\n';
}
