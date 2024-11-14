#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 202020;

int n, m;
struct Edge { int idx, v; };
vector<Edge> adj[MAXN];

int dep[MAXN], par[MAXN], to_par[MAXN];

int opt = 0;
int optu = -1, optv = -1, opt_idx = -1;

void dfs(int v, int prv) {
    dep[v] = 1 + dep[prv];
    par[v] = prv;

    for (auto [idx, u] : adj[v]) {
        if (u == prv) continue;

        if (dep[u] == 0) {
            to_par[u] = idx;
            dfs(u, v);
        } else if (dep[u] < dep[v]) {
            if (opt < dep[u]) {
                opt = dep[u];
                optu = u, optv = v, opt_idx = idx;
            }
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

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back({i + 1, v});
        adj[v].push_back({i + 1, u});
    }

    dfs(1, 0);

    cout << (dep[optv] - dep[optu] + 1) << '\n';
    int now = optv;
    while (now != optu) {
        cout << to_par[now] << ' ';
        now = par[now];
    }
    cout << opt_idx;
}
