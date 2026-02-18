#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

void dfs(int now, const vector<vector<int>> &g, vector<bool> &vis) {
    vis[now] = 1;
    for (int nxt : g[now]) if (!vis[nxt]) dfs(nxt, g, vis);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
    }

    int a, b;
    cin >> a >> b;
    a--, b--;

    vector<bool> vis_a(n), vis_b(n);
    dfs(a, g, vis_a);
    dfs(b, g, vis_b);

    for (int i = 0; i < n; i++) {
        if (vis_a[i] && vis_b[i]) {
            cout << "yes\n";
            cout << i + 1 << '\n';
            exit(0);
        }
    }
    cout << "no\n";
}
