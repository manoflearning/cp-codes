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

vector<bool> is_b;
vector<int> dp1, dp2;

void init() {
    // TODO
}

void input() {
    cin >> n;
    t.assign(n + 1, vector<int>());

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        t[u].push_back(v);
        t[v].push_back(u);
    }

    is_b.assign(n + 1, 0);
}

void dfs1(int v, int prv) {
    for (auto &i : t[v]) {
        if (i == prv) continue;
        if (is_b[i]) continue;
        dfs1(i, v);
        dp1[v] = max(dp1[v], dp1[i] + 1);
    }
}

void dfs2(int v, int prv) {
    int mx1 = -2, mx2 = -2;
    for (auto &i : t[v]) {
        if (i == prv) continue;
        if (is_b[i]) continue;

        if (mx1 <= dp1[i]) {
            mx2 = mx1;
            mx1 = dp1[i];
        } else if (mx2 < dp1[i]) {
            mx2 = dp1[i];
        }
    }

    for (auto &i : t[v]) {
        if (i == prv) continue;
        if (is_b[i]) continue;

        int res = 1 + dp2[v];
        res = max(res, 2 + (dp1[i] == mx1 ? mx2 : mx1));

        dp2[i] = res;
        dfs2(i, v);
    }
}

pair<int, int> find_dc() {
    int dia = 0;

    vector<int> mx1(n + 1), mx2(n + 1);
    for (int v = 1; v <= n; v++) {
        if (is_b[v]) continue;

        mx1[v] = dp2[v];
        for (auto &i : t[v]) {
            if (is_b[i]) continue;

            if (1 + dp1[i] <= dp1[v]) {
                if (mx1[v] <= 1 + dp1[i]) {
                    mx2[v] = mx1[v];
                    mx1[v] = 1 + dp1[i];
                } else if (mx2[v] < 1 + dp1[i]) {
                    mx2[v] = 1 + dp1[i];
                }
            }
        }

        dia = max(dia, mx1[v] + mx2[v]);
    }

    int opt = -1, opt_val = 1e9;
    for (int v = 1; v <= n; v++) {
        if (is_b[v]) continue;
        // cout << dia << ' ' << mx1[v] << ' ' << mx2[v] << '\n';
        // if (dia == mx1[v] + mx2[v]) cout << v << ' ';
        if (dia == mx1[v] + mx2[v] && max(dp1[v], dp2[v]) < opt_val) {
            opt = v;
            opt_val = max(dp1[v], dp2[v]);
        }
    }
    // cout << '\n';
    return {opt, opt_val};
}

void coloring(int v, int prv, int d) {
    if (d == 0) {
        is_b[v] = 1;
        return;
    }

    for (auto &i : t[v]) {
        if (i == prv) continue;
        if (is_b[i]) continue;
        coloring(i, v, d - 1);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        vector<pii> ans;

        while (1) {
            dp1.assign(n + 1, 0);
            dp2.assign(n + 1, 0);

            int ans_v = -1, ans_d = -1;

            for (int v = 1; v <= n; v++) {
                if (is_b[v]) continue;
                dfs1(v, 0);
                dfs2(v, 0);
                auto res = find_dc();
                ans_v = res.fr, ans_d = res.sc;
                break;
            }

            if (ans_v == -1) break;

            ans.push_back({ans_v, ans_d});

            coloring(ans_v, 0, ans_d);

            // for (int v = 1; v <= n; v++) {
            //     cout << v << ' ' << dp1[v] << ' ' << dp2[v] << '\n';
            // }

            // cout << ans_v << ' ' << ans_d << '\n';
        }

        // assert(sz(ans) <= (n + 1) / 2);

        cout << sz(ans) << '\n';
        for (auto &[v, d] : ans) {
            cout << v << ' ' << d << '\n';
        }
    }
}
