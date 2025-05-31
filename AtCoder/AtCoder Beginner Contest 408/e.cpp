#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 202020;

int n, m;
struct Edge {
    int w, v;
    int idx;
    bool can_use;
};
vector<Edge> adj[N];

void input() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({w, v, 2 * i, 1});
        adj[v].push_back({w, u, 2 * i + 1, 1});
    }
}

bool vis[N];
bool dfs(int v) {
    vis[v] = 1;
    if (v == n) return 1;
    bool ret = 0;
    for (auto &e : adj[v]) {
        if (!e.can_use) continue;
        if (vis[e.v]) continue;
        ret |= dfs(e.v);
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    int ans = 0;
    for (int i = 29; i >= 0; i--) {
        vector<int> changed;
        for (int v = 1; v <= n; v++) {
            for (auto &e: adj[v]) {
                if ((e.w & (1 << i)) && e.can_use) {
                    e.can_use = 0;
                    changed.push_back(e.idx);
                }
            }
        }

        memset(vis, 0, sizeof(vis));
        bool res = dfs(1);

        if (res) continue;

        ans |= (1 << i);
        int flag = 0;
        for (int v = 1; v <= n; v++) {
            for (auto &e: adj[v]) {
                if ((e.w & (1 << i)) && !e.can_use && (flag < sz(changed) && changed[flag] == e.idx)) {
                    e.can_use = 1;
                    flag++;
                }
            }
        }
    }

    cout << ans;
}
