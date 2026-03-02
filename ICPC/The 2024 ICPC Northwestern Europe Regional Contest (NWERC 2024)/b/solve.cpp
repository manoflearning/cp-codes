#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

const int inf = 1e9;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, m; cin >> n >> m;
    vi a(n); rep(i,0,n) cin >> a[i];

    if(*max_element(all(a)) == *min_element(all(a))) {
        cout << 1 << '\n';
        return 0;
    }

    vector<vi> adj(n);
    vector<vi> ind(n, vi(2, 0));
    for(int i = 0; i < m; i++) {
        int u,v; cin >> u >> v;
        u--, v--;
        ind[u][a[v]]++;
        ind[v][a[u]]++;

        adj[v].push_back(u);
        adj[u].push_back(v);
    }

    vi dp(n, inf);
    priority_queue<pii, vector<pii>, greater<>> q;

    for(int i = 0; i < n; i++) {
        if(ind[i][0] == 0 || ind[i][1] == 0) {
            dp[i] = 1;
            q.push({1, i});
        }
    }

    vector<vector<multiset<int>>> count(n, vector<multiset<int>>(2));

    vi rmv(n, -1);

    while(sz(q)) {
        auto [d, u] = q.top(); q.pop();
        if(dp[u] != d) continue;

        // cout << u << ' ' << d << '\n'; cout.flush();

        for(auto &v:adj[u]) {
            // cout << u << ' ' << v << '\n'; cout.flush();
            if(~rmv[u]) {
                auto it = count[v][a[u]].find(rmv[u]);
                if(it != count[v][a[u]].end()) count[v][a[u]].erase(it);

                count[v][a[u]].insert(d);

                if(dp[v] > (1 + *count[v][a[u]].rbegin())) {
                    if(!~rmv[v]) rmv[v] = dp[v];

                    dp[v] = min(dp[v], 1 + *count[v][a[u]].rbegin());
                    q.push({dp[v], v});
                }
            }
            else if(ind[v][a[u]]) {
                ind[v][a[u]]--;
                count[v][a[u]].insert(d);

                if(ind[v][a[u]] == 0 && dp[v] > (1 + *count[v][a[u]].rbegin())) {
                    if(!~rmv[v]) rmv[v] = dp[v];

                    dp[v] = min(dp[v], 1 + *count[v][a[u]].rbegin());
                    q.push({dp[v], v});
                }
            }
        }

        rmv[u] = -1;
    }

    int ans = 0;
    for(auto &t:dp) {
        // cout << t << ' ';
        ans = max(t, ans);
    }

    if(ans >= inf) cout << "infinity\n";
    else cout << ans + 1 << '\n';
}
