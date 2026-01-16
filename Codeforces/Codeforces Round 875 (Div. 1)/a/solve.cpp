#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int n;
struct Edge {
    int v, idx;
};
vector<vector<Edge>> t;

vector<int> dp;

void input() {
    cin >> n;
    t.assign(n + 1, vector<Edge>{});
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        t[u].push_back({v, i + 1});
        t[v].push_back({u, i + 1});
    }

    dp.assign(n + 1, 0);
}

void dfs(int now, int prv, int ord) {
    dp[now] = 1;

    for (const auto &[nxt, idx] : t[now]) {
        if (nxt == prv) continue;
        dfs(nxt, now, idx);

        dp[now] = max(dp[now], dp[nxt] + (idx < ord));
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        input();

        dfs(1, 0, 0);

        cout << dp[1] << '\n';
    }
}
