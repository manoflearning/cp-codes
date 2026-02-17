#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

void dfs(int now, vector<int> &a, const vector<vector<int>> &g, vector<bool> &vis) {
    vis[now] = 1;
    a.push_back(now);

    for (int nxt : g[now]) {
        if (!vis[nxt]) dfs(nxt, a, g, vis);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> ans(n);
    vector<bool> vis(n);
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        vector<int> a;
        dfs(i, a, g, vis);
        if (sz(a) < k) {
            cout << "impossible\n";
            exit(0);
        }
        for (int j = 0; j < sz(a); j++) {
            ans[a[j]] = min(k, j + 1);
        }
    }

    for (auto &i : ans) cout << i << ' ';
}
