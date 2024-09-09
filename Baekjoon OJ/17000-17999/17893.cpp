#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<tuple<int, int, double>> p;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        double w; cin >> w;
        p.push_back({ u - 1, v - 1, w });
    }

    // base case
    vector<double> dp(1 << n, 0);
    dp[0] = 1;

    // inductive step
    for (int k = 0; k < m; k++) {
        vector<double> tmp(1 << n, 0);
        for (int bit = 0; bit < (1 << n); bit++) {
            if (bit & (1 << get<0>(p[k]))) {
                tmp[bit] += dp[bit];
            } else if (bit & (1 << get<1>(p[k]))) {
                tmp[bit] += dp[bit];
            } else {
                tmp[bit] += dp[bit] * (1 - get<2>(p[k]));
                tmp[bit | (1 << get<1>(p[k]))] += dp[bit] * get<2>(p[k]);
            }
        }
        dp = tmp;
    }

    cout << fixed;
    cout.precision(8);

    vector<double> ans(n, 0);
    for (int bit = 0; bit < (1 << n); bit++) {
        for (int i = 0; i < n; i++) {
            ans[i] += dp[bit] * !(bit & (1 << i));
        }
    }

    for (auto& i : ans)
        cout << i << '\n';
}
