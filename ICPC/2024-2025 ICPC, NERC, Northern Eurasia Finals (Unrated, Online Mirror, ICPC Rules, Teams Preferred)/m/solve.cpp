#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

void sol() {
    int n; cin >> n;
    vi a(2*n); rep(i, 0, 2*n) { cin >> a[i]; a[i]--; }

    vector<vi> adj(2 * n);
    for(int i = 0; i < 2 * n - 1; i++) {
        int u,v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<pii> prs;
    vi pt(2 * n, -1), nm(2 * n);

    function<int(int, int)> dfs = [&](int u, int p) -> int{
        vi nx;
        for(auto &v:adj[u]) {
            if(v == p) continue;
            auto res = dfs(v, u);
            if(~res) nx.push_back(res);
        }

        if(sz(nx)) {
            prs.push_back({nx[0], u});

            pt[nx[0]] = u, pt[u] = nx[0];
            return -1;
        }else return u;
    };

    dfs(0, -1);

    function<int(int)> dfs2 = [&](int u) -> int{
        if(~pt[nm[u]]) return dfs2(pt[nm[u]]);
        return nm[u];
    };

    vector<vi> pos(n);

    for(int i = 0; i < 2 * n; i++) {
        pos[a[i]].push_back(i);
    }

    for(int i = 0; i < n; i++) {
        nm[pos[i][0]] = pos[i][1];
        nm[pos[i][1]] = pos[i][0];
    }

    for(int i = 0; i < 2 * n; i++) {
        if(pt[i] == -1) {
            int v = dfs2(i);
            pt[v] = i;
            pt[i] = v;

            // cout << pt[v] << ' ' << pt[i] << '\n';            
        }
    }

    set<pii> ans;
    vi vis(2 * n);
    function<void(int, int)> dfs3 = [&](int u, int up) -> void{
        vis[up] = vis[nm[u]] = 1;
        // cout << u << ' ' << up << endl;

        if(up == nm[u]) return;
        ans.insert({min(up, nm[u]), max(up, nm[u])});

        if(vis[nm[up]] || vis[pt[nm[u]]]) return;
        dfs3(up, pt[nm[u]]);
    };

    for(int i = 0; i < 2 * n; i++) {
        if (!vis[i]) dfs3(i, pt[i]);
    }

    cout << sz(ans) << '\n';
    for(auto &[l, r]:ans) cout << l + 1 << ' ' << r + 1 << '\n';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while(tc--) sol();
}
