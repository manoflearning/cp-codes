#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const ll INF = 1e18;

int n;
struct Edge { ll w; int v; };
vector<Edge> t[101010];

void input() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        t[u].push_back({ w, v });
        t[v].push_back({ w, u });
    }
}

int r = -1;
pair<ll, ll> dp[101010][2];

void dfs(int v, int prv) {
    dp[v][0] = { 0, 0 };
    dp[v][1] = { 0, 0 };

    for (auto& i : t[v]) {
        if (i.v == prv) continue;

        dfs(i.v, v);

        pair<ll, ll> res0 = dp[v][0];
        pair<ll, ll> res1 = dp[v][1];

        auto [w0, left0] = dp[i.v][0];

        res0.first = max(res0.first, dp[v][0].first + w0);
        res1.first = max(res1.first, dp[v][1].first + w0);

        auto [w1, left1] = dp[i.v][1];
        left1 += i.w;

        res0.first = max(res0.first, dp[v][1].first + dp[v][1].second + w1 + left1);
        res1.first = max(res1.first, dp[v][0].first + w1);
        res1.second = left1;

        dp[v][0] = res0;
        dp[v][1] = res1;
    }

    cout << v << '\n';
    cout << dp[v][0].first << '\n';
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    if (n == 2) {
        cout << t[1][0].w;
        return 0;
    }

    for (int v = 1; v <= n; v++) {
        if (sz(t[v]) >= 2) { r = v; break; }
    }

    dfs(r, -1);

    cout << max(dp[r][0].first, dp[r][1].first);
}