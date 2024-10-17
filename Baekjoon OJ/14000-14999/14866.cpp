#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const int MAXN = 303030;

int n, m;
vector<int> adj[MAXN], chd[MAXN];

void input() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

bool is_in[MAXN], is_out[MAXN];
int to_par[MAXN], f[MAXN], h[MAXN];

void dfs(int v, int prv) {
    is_in[v] = 1;

    for (auto& i : adj[v]) {
        if (i == prv) continue;

        if (is_in[i] && !is_out[i]) {
            f[i]++;
            h[v]++;
        } else if (!is_in[i]) {
            int tmp = f[v];
            dfs(i, v);
            chd[v].push_back(i);
            to_par[i] += (f[v] - tmp);
            f[v] += f[i];
            h[v] += h[i];
        }
    }

    is_out[v] = 1;
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

    ll ans = 0;
    for (int v = 1; v <= n; v++) {
        bool case1 = (m - n + 1 - h[v] <= 0);
        bool case2 = 1;
        bool case3 = 1;
        for (auto& u : chd[v]) {
            if (f[u] > 0) case2 = 0;
            if (h[u] - to_par[u] >= 2) case3 = 0;
        }
        if (case1 && case2 && case3) ans += v;
    }

    cout << ans;
}
