#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int n, m;
vector<pii> a;
vector<vector<int>> adj;
vector<int> dist;

void bfs() {
    dist.assign(n + 1, -1);

    queue<int> qu;
    qu.push(1);
    dist[1] = 0;
    while (!qu.empty()) {
        const int now = qu.front();
        qu.pop();

        for (int nxt : adj[now]) {
            if (dist[nxt] != -1) continue;
            dist[nxt] = dist[now] + 1;
            qu.push(nxt);
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        cin >> n >> m;

        a.clear();
        adj.assign(n + 1, vector<int>());
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            if (u == 1) continue;
            a.push_back({u, v});
            adj[v].push_back(u);
        }
        
        bfs();

        bool infinite = 0;
        for (int v = 1; v <= n; v++) {
            if (dist[v] == -1) infinite = 1;
        }

        if (infinite) {
            cout << "INFINITE\n";
            continue;
        }

        cout << "FINITE\n";

        vector<int> ord(n - 1);
        iota(all(ord), 2);
        sort(all(ord), [&](int i, int j) {
            return dist[i] > dist[j];
        });
        
        vector<int> ans;
        for (int v : ord) ans.push_back(v);
        ans.push_back(1);
        for (int v : ord) ans.push_back(v);
        for (int lb = 2; lb <= n; lb++) {
            for (int v : ord) if (dist[v] >= lb) ans.push_back(v);
        }

        cout << sz(ans) << '\n';
        for (auto &i : ans) cout << i << ' ';
        cout << '\n';
    }
}
