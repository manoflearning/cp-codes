#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int dp[5050][5050];

void run(int u, int v, const vector<vector<vi>>& adj, const vector<vector<vi>>& rev){
    if(~dp[u][v]) return;
    dp[u][v]=1;
    
    for(int i = 0; i < 26; i++) {
        for(auto &nu:rev[u][i]) {
            for(auto &nv:adj[v][i]) {
                run(nu, nv, adj, rev);
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n,m; cin >> n >> m;
    vector<vector<vi>> adj(n + 1, vector<vi>(26));
    vector<vector<vi>> rev(n + 1, vector<vi>(26));
    vector<pii> edge;

    for(int i = 0; i < m; i++) {
        int u,v; char c;
        cin >> u >> v >> c;
        u--; v--; c -= 'a';
        adj[u][c].push_back(v);
        rev[v][c].push_back(u);

        edge.push_back({u,v});
    }

    memset(dp, -1, sizeof(dp));

    for(int i = 0; i < n; i++) {
        run(i,i, adj, rev);
    }
    for(int i = 0; i < m; i++) {
        run(edge[i].first, edge[i].second, adj, rev);
    }

    int ans=0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i == j) continue;
            if(dp[i][j] == 1) ans++;

            // if(dp[i][j] == 1) cout << i << ' ' << j << '\n';
        }
    }

    cout << ans << '\n';
}
