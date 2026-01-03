#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

constexpr int INF = 1e9 + 7;

int n;
vector<vector<int>> t;
vector<int> dep, mx_dep;

void init() {
    t.clear();
    dep.clear();
    mx_dep.clear();
}

void input() {
    cin >> n;
    t.resize(n + 1);
    dep.resize(n + 1);
    mx_dep.resize(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        t[u].push_back(v);
        t[v].push_back(u);
    }
}

void dfs(int v, int prv) {
    dep[v] = dep[prv] + 1;
    mx_dep[v] = dep[v];
    for (auto &i : t[v]) {
        if (i == prv) continue;
        dfs(i, v);
        mx_dep[v] = max(mx_dep[v], mx_dep[i]);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        dfs(1, 0);

        vector<ll> psum(n + 2);
        for (int v = 2; v <= n; v++) {
            int p = dep[v], q = mx_dep[v];
            psum[1]++, psum[p]--;
            psum[q + 1]++, psum[n + 1]--;
        }

        ll ans = INF;
        for (int i = 1; i <= n; i++) {
            psum[i] += psum[i - 1];
            ans = min(ans, psum[i]);
        }
        cout << ans << '\n';
    }
}
