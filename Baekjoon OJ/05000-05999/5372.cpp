#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define sz(x) (int)(x).size()

const int INF = 1e9 + 7;

int n, k, m;
vector<pii> e;
bool vis[55];

void init() {
    e.clear();
    memset(vis, 0, sizeof(vis));
}

void input() {
    cin >> n >> k >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        e.push_back({u, v});
    }
}

int bt(int idx, int cnt) {
    if (idx == m) return cnt;
    auto [u, v] = e[idx];
    if (vis[u] || vis[v]) return bt(idx + 1, cnt);

    if (cnt == k) return INF;
    if (cnt < k) {
        int ret = INF;
        vis[u] = 1;
        ret = min(ret, bt(idx + 1, cnt + 1));
        vis[u] = 0;

        vis[v] = 1;
        ret = min(ret, bt(idx + 1, cnt + 1));
        vis[v] = 0;
        return ret;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        int ans = bt(0, 0);
        if (ans <= k) cout << ans << '\n';
        else cout << "IMPOSSIBLE\n";
    }
}
