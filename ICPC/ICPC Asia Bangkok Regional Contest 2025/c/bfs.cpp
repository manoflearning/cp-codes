#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int X = 202020;
constexpr int BASE = 6 * X;

int dist[BASE << 1];
int opt[BASE << 1];

void bfs() {
    memset(dist, -1, sizeof(dist));

    queue<int> qu;

    dist[BASE + 1] = 1, opt[BASE + 1] = 1;
    qu.push(BASE + 1);

    while (!qu.empty()) {
        auto v = qu.front();
        qu.pop();

        // cout << v - BASE << ' ' << dist[v] << ' ' << opt[v] << '\n';

        int w = dist[v] + 1;
        for (int i = -1; i <= 1; i += 2) {
            int u = v + i * w;
            if (u < 0 || 2 * BASE <= u) continue;
            if (dist[u] != -1) continue;
            dist[u] = w, opt[u] = i;
            qu.push(u);
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);
    
    bfs();

    int tc; cin >> tc;
    while (tc--) {
        int x; cin >> x;

        cout << dist[x + BASE] << '\n';
        vector<pii> ans;

        int now = x + BASE;
        while (dist[now] > 1) {
            ans.push_back({opt[now], dist[now]});
            now -= opt[now] * dist[now];
        }
        ans.push_back({1, 1});

        for (int i = sz(ans) - 1; i >= 0; i--) {
            if (i == sz(ans) - 1) cout << ans[i].sc;
            else cout << (ans[i].fr > 0 ? '+' : '-') << ans[i].sc;
        }
        cout << '\n';
    }
}