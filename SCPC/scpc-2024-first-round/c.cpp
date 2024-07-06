// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define sz(x) (int)(x).size()
#define all(c) (c).begin(), (c).end()

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        int n; cin >> n;
        vector<int> cnt(n + 1);

        vector<pii> e;
        for (int i = 0; i < n + 1; i++) {
            int u, v;
            cin >> u >> v;
            cnt[u]++, cnt[v]++;
            e.push_back({ u, v });
        }

        vector<vector<int>> adj(n + 1);
        bool passed = 0;
        for (auto& [u, v] : e) {
            if (cnt[u] == 3 && cnt[v] == 3 && !passed) {
                passed = 1;
                continue;
            }
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> dist(n + 1, -1);
        int now = 1;
        dist[now] = 1;
        while (dist[adj[now][0]] == -1 || dist[adj[now][1]] == -1) {
            for (auto& nxt : adj[now]) {
                if (dist[nxt] != -1) continue;
                dist[nxt] = dist[now] + 1;
                now = nxt;
                break;
            }
        }

        ll len = 0;
        for (int v = 1; v <= n; v++) {
            // cout << v << ' ' << dist[v] << '\n';
            if (cnt[v] == 3) {
                if (len == 0) len += dist[v];
                else len -= dist[v];
            }
        }
        len = abs(len);

        // cout << len << '\n';

        ll ans = 0;
        ans += len * (len - 1) / 2;
        ans += (n - len) * (n - len - 1) / 2;

        cout << ans << '\n';

        cout << flush;
    }
}