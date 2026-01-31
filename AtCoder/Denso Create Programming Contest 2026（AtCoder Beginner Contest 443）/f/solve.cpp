#pragma GCC optimize ("Ofast")
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

    int n; cin >> n;

    const int mod = n;

    vector<vector<int>> dist(n, vector<int>(10, -1));
    vector<vector<pii>> opt(n, vector<pii>(10, {-1, -1}));

    queue<pii> qu;
    dist[0][0] = 0;
    qu.push({0, 0});

    bool stop = 0;
    while (!qu.empty() && !stop) {
        const auto [rem, d] = qu.front();
        qu.pop();

        for (int nd = d; nd < 10; nd++) {
            const int nrem = (10 * rem + nd) % mod;
            if (dist[nrem][nd] != -1) continue;
            dist[nrem][nd] = dist[rem][d] + 1;
            opt[nrem][nd] = {rem, d};
            qu.push({nrem, nd});

            if (nrem == 0) {
                stop = 1;
                break;
            }
        }
    }

    int opt_d = -1;
    for (int d = 1; d < 10; d++) {
        if (dist[0][d] == -1) continue;
        if (opt_d == -1 || dist[0][opt_d] > dist[0][d]) opt_d = d;
    }

    if (opt_d == -1) {
        cout << -1 << '\n';
        return 0;
    }

    string ans{};

    int opt_rem = 0;
    while (dist[opt_rem][opt_d] > 0) {
        ans.push_back('0' + opt_d);

        auto prv = opt[opt_rem][opt_d];
        opt_rem = prv.first, opt_d = prv.second;
    }

    reverse(all(ans));

    cout << ans << '\n';

    return 0;
}
