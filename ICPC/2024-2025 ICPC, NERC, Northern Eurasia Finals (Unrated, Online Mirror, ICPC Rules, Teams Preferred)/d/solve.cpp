#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    vector<pii> arr;
    for(int i = 0; i < n; i++) {
        string type, tf; cin >> type >> tf;
        int v = type == "set";
        int u = v ^ (tf == "true");
        arr.push_back({u,v});
    }

    int m; cin >> m;
    vi ind(n);
    vector<vi> adj(n);
    for(int i = 0; i < m; i++) {
        int u,v; cin >> u >> v;
        u--, v--;

        adj[u].push_back(v);
        ind[v]++;
    }

    queue<int> q[2][2];
    int now = 0;

    vi vis(n, 0);
    vi ans;

    for(int i = 0; i < n; i++) {
        auto &[u,v] = arr[i];

        if(ind[i] == 0) q[u][v].push(i);
    }
    
    while(sz(q[now][0]) || sz(q[now][1])) {
        int u;
        if(sz(q[now][now])) u = q[now][now].front(), q[now][now].pop();
        else u = q[now][now ^ 1].front(), q[now][now ^ 1].pop();

        vis[u] = 1;
        ans.push_back(u + 1);

        for(auto &v:adj[u]) {
            ind[v]--;

            if(ind[v] == 0) {
                auto &[vu, vv] = arr[v];
                q[vu][vv].push(v);
            }
        }

        now = arr[u].second;
    }

    if(sz(ans) < n) cout << -1 << '\n';
    else
        for(auto &out:ans) cout << out << ' ';
}
