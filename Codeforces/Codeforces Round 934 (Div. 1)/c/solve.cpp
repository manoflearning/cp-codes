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

int n;
vector<vector<int>> t;
int a = -1, b = -1, opt_a = 0, opt_b = 0;
vector<int> par;

void input() {
    cin >> n;
    t.assign(n + 1, vector<int>());

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        t[u].push_back(v);
        t[v].push_back(u);
    }
    a = b = -1;
    opt_a = opt_b = 0;

    par.assign(n + 1, 0);
}

void dfs(int v, int prv, int dist, int &u, int &opt) {
    if (opt < dist) {
        u = v;
        opt = dist;
    }
    par[v] = prv;

    for (auto &i : t[v]) {
        if (i != prv) dfs(i, v, dist + 1, u, opt);
    }
}

pii get_center() {
    int now = b;
    int dist = -1;

    if (opt_b & 1) {
        dist = opt_b / 2;
        while (dist--) now = par[now];
        return {now, -1};
    } else {
        dist = opt_b / 2 - 1;
        while (dist--) now = par[now];
        return {now, par[now]};
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        input();

        dfs(1, 0, 1, a, opt_a);
        dfs(a, 0, 1, b, opt_b);

        auto [c1, c2] = get_center();
        
        vector<pii> ans;
        if (c2 == -1) {
            for (int d = 0; d <= opt_b / 2; d++) {
                ans.push_back({c1, d});
            }
        } else {
            for (int d = 1; d <= opt_b / 2; d += 2) {
                ans.push_back({c1, d});
                ans.push_back({c2, d});
            }
        }

        cout << sz(ans) << '\n';
        for (auto &i : ans)
            cout << i.fr << ' ' << i.sc << '\n';
    }
}
