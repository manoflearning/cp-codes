#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

const int MAXN = 101010;

int n, m;
vector<int> adj[MAXN];

int vi[MAXN], par[MAXN], dep[MAXN], used[MAXN];
void dfs(int v, int prv) {
    vi[v] = 1;
    par[v] = prv;
    dep[v] = dep[prv] + 1;

    for (auto& i : adj[v]) {
        if (!vi[i]) dfs(i, v);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int v = 1; v <= n; v++) {
        if (!vi[v]) dfs(v, 0);
    }

    vector<int> ord;
    for (int v = 1; v <= n; v++) ord.push_back(v);

    sort(all(ord), [&](const int p1, const int p2) {
        return dep[p1] > dep[p2];
    });

    vector<vector<int>> ans;
    for (auto& v : ord) {
        vector<int> chd;
        for (auto& i : adj[v])
            if (dep[i] > dep[v] && !(par[i] == v && used[i])) chd.push_back(i);

        if (sz(chd) % 2 == 1 && dep[v] > 1) {
            used[v] = 1;
            ans.push_back({ chd.back(), v, par[v] });
        }

        for (int i = 0; i + 1 < sz(chd); i += 2) {
            ans.push_back({ chd[i], v, chd[i + 1] });
        }
    }

    cout << sz(ans) << '\n';
    for (auto& i : ans)
        cout << i[0] << ' ' << i[1] << ' ' << i[2] << '\n';
}