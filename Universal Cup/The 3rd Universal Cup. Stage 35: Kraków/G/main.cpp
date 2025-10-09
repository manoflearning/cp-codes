#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

const int N = 202020;
const int D = 18;

int n, q, c;
struct Edge {
    int v; ll w;
};
vector<Edge> adj[N];

int par[D][N], dep[N];
ll dist[D][N];
int dp[D][N];

void init() {
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
    }
}

void input() {
    cin >> n >> q >> c;
    for (int i = 0; i < n - 1; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
}

void dfs0(int v, int prv) {
    for (auto &i : adj[v]) {
        if (i.v != prv) {
            par[0][i.v] = v;
            dist[0][i.v] = i.w;
            dep[i.v] = dep[v] + 1;
            dfs0(i.v, v);
        }
    }
}

int hrv(int v, ll w) {
    int ret = v;
    for (int d = D - 1; d >= 0; d--) {
        if (dist[d][ret] > w || par[d][ret] == 0) continue;

        w -= dist[d][ret];
        ret = par[d][ret];
    }
    return ret;
}

void build_sparse_table() {
    dep[1] = 1;
    dfs0(1, 0);
    for (int d = 0; d + 1 < D; d++) {
        for (int v = 1; v <= n; v++) {
            par[d + 1][v] = par[d][par[d][v]];
            dist[d + 1][v] = dist[d][v] + dist[d][par[d][v]];
        }
    }

    for (int v = 1; v <= n; v++) {
        dp[0][v] = hrv(v, c);
    }
    for (int d = 0; d + 1 < D; d++) {
        for (int v = 1; v <= n; v++) {
            dp[d + 1][v] = dp[d][dp[d][v]];
        }
    }
}

pair<int, ll> lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int diff = dep[u] - dep[v];
    ll ret2 = 0;
    for (int i = D - 1; i >= 0; i--) {
        if (diff & (1 << i)) {
            ret2 += dist[i][u];
            u = par[i][u];
        }
    }
    if (u == v) return {u, ret2};
    for (int i = D - 1; i >= 0; i--) {
        if (par[i][u] ^ par[i][v]) {
            ret2 += dist[i][u];
            ret2 += dist[i][v];
            u = par[i][u];
            v = par[i][v];
        }
    }
    return {par[0][u], ret2 += dist[0][u] + dist[0][v]};
}

pair<int, int> mov(int v, int target_dep) {
    pair<int, int> ret{0, v};
    int now = v;
    for (int d = D - 1; d >= 0; d--) {
        if (dep[dp[d][now]] <= target_dep) continue;
        // cout << "fuck " << now << ' ' << d << ' ' << dp[d][now] << '\n';

        ret.first += (1 << d);
        ret.second = now = dp[d][now];
    }

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        build_sparse_table();

        while (q--) {
            int u, v;
            cin >> u >> v;

            if (u == v) {
                cout << 0 << '\n';
                continue;
            }

            int lc = lca(u, v).first;
            
            auto [cnt1, v1] = mov(u, dep[lc]);
            auto [cnt2, v2] = mov(v, dep[lc]);
            // cout << cnt1 << ' ' << v1 << '\n';
            // cout << cnt2 << ' ' << v2 << '\n';

            ll w_rem = lca(v1, v2).second;
            // cout << "v1 = " << v1 << ", v2 = " << v2 << '\n';
            // cout << "w_rem = " << w_rem << '\n';

            ll ans = cnt1 + cnt2;

            if (w_rem == 0) ans--;
            else if (w_rem <= c) ;
            else if (w_rem <= 2 * c) ans++;
            else assert(0);

            cout << ans << '\n';
            // cout << '\n';
        }
    }
}
