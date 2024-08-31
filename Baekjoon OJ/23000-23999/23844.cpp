#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 10101;

int n, k;
vector<int> adj[MAXN];
int dep[MAXN], par[MAXN];
vector<int> dep_to_v[MAXN];
int siz[MAXN];

void input() {
    cin >> n >> k;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void dfs(int v, int prv) {
    dep[v] = dep[prv] + 1;
    par[v] = prv;
    siz[v] = 1;
    dep_to_v[dep[v]].push_back(v);
    for (auto& i : adj[v]) {
        if (i != prv) dfs(i, v);
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

    dep[1] = 1;
    dfs(1, 0);

    int ans = n;

    for (int d = MAXN - 1; d >= 1; d--) {
        if (dep_to_v[d].empty()) continue;

        if (sz(dep_to_v[d]) <= k) continue;

        sort(all(dep_to_v[d]), [&](int p1, int p2) {
            return siz[p1] < siz[p2];
        });

        for (int i = 0; i < sz(dep_to_v[d]) - k; i++) {
            int v = dep_to_v[d][i];
            if (i < sz(dep_to_v[d]) - k) ans -= siz[v];
            else siz[par[v]] += siz[v];
        }
    }

    cout << ans;
}
