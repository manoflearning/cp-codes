#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ll INF = 4e18;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;

        vector<vector<ll>> a(n, vector<ll>(m));
        for (auto &i : a) for (auto &j : i) cin >> j;

        vector<vector<ll>> dp1(n, vector<ll>(m, -INF)), dp2(n, vector<ll>(m, -INF));
        dp1[0][0] = a[0][0];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i > 0) dp1[i][j] = max(dp1[i][j], dp1[i - 1][j] + a[i][j]);
                if (j > 0) dp1[i][j] = max(dp1[i][j], dp1[i][j - 1] + a[i][j]);
            }
        }

        dp2[n - 1][m - 1] = a[n - 1][m - 1];
        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                if (i + 1 < n) dp2[i][j] = max(dp2[i][j], dp2[i + 1][j] + a[i][j]);
                if (j + 1 < m) dp2[i][j] = max(dp2[i][j], dp2[i][j + 1] + a[i][j]);
            }
        }

        ll ans = INF;
        for (int i = 0; i < n; i++) {
            vector<ll> ps(m);
            if (i + 1 < n) {
                for (int j = 0; j < m; j++) {
                    ps[j] = dp1[i][j] + dp2[i + 1][j];
                    if (j > 0) ps[j] = max(ps[j], ps[j - 1]);
                }
            }
            
            vector<ll> ss(m);
            if (i > 0) {
                for (int j = m - 1; j >= 0; j--) {
                    ss[j] = dp1[i - 1][j] + dp2[i][j];
                    if (j + 1 < m) ss[j] = max(ss[j], ss[j + 1]);
                }
            }
            
            for (int j = 0; j < m; j++) {
                ll res = dp1[i][j] + dp2[i][j] - 3 * a[i][j];

                if (i + 1 < n && j > 0) res = max(res, ps[j - 1]);
                if (i > 0 && j + 1 < m) res = max(res, ss[j + 1]);

                ans = min(ans, res);
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
