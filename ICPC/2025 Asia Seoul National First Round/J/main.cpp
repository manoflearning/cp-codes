#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define sz(x) (int)(x).size()

const int N = 1010;

int n, m;
ll lvl[N];
vector<int> adj[N];
bool linked[N][N];
ll fr_mx[N][N], sc_mx[N][N];
// vector<pii> pairs;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> lvl[i];
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        linked[u][v] = linked[v][u] = 1;
    }

    for (int v = 1; v <= n; v++) {
        for (int i = 0; i < sz(adj[v]); i++) {
            for (int j = i + 1; j < sz(adj[v]); j++) {
                int p = adj[v][i], q = adj[v][j];

                ll val = lvl[v];
                if (p > q) swap(p, q);
                
                if (val >= fr_mx[p][q]) {
                    sc_mx[p][q] = fr_mx[p][q];
                    fr_mx[p][q] = val;
                } else if (val > sc_mx[p][q]) {
                    sc_mx[p][q] = val;
                }
            }
        }
    }

    ll ans = -1;
    for (int p = 1; p <= n; p++) {
        for (int q = p + 1; q <= n; q++) {
            if (sc_mx[p][q] == 0) continue;
            ans = max(ans, lvl[p] + lvl[q] + fr_mx[p][q] + sc_mx[p][q]);
        }
    }

    cout << ans;
}
