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

    int n, m;
    cin >> n >> m;

    vector<unordered_set<int>> g(n), rg(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].insert(v);
        rg[v].insert(u);
    }

    int ans1{-1}, ans2{-1};
    for (int i = 0; i < n; i++) {
        int res = 0;
        for (int j : rg[i]) res += !g[i].count(j);
        if (ans2 < res) ans1 = i, ans2 = res;
    }

    cout << ans1 + 1 << ' ' << ans2 << '\n';
}
