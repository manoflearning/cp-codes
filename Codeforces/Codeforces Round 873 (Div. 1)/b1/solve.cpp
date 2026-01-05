#pragma GCC optimize("O3")
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

constexpr int MOD = 1e9 + 7;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> a(n + 1), cc(1);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            cc.push_back(a[i]);
        }

        sort(all(cc));
        cc.erase(unique(all(cc)), cc.end());

        vector<vector<int>> psum(n + 1, vector<int>(n + 1));
        for (int i = 1; i <= n; i++) {
            a[i] = lower_bound(all(cc), a[i]) - cc.begin();
            psum[a[i]][i]++;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                psum[i][j] += psum[i - 1][j];
                psum[i][j] += psum[i][j - 1];
                psum[i][j] -= psum[i - 1][j - 1];
            }
        }

        ll ans = 0;

        for (int i = 1; i <= n; i++) {
            ll acc = 0;

            vector<pii> lr;
            // int prv_l = 0, prv_r = 0;
            for (int j = i + 1; j <= n; j++) {
                int cnt = psum[a[j] - 1][j] - psum[a[j] - 1][i - 1];

                int l = i + cnt, r = j;

                while (!lr.empty() && l <= lr.back().sc) {
                    l = min(l, lr.back().fr);
                    acc -= lr.back().sc - lr.back().fr;
                    lr.pop_back();
                }

                lr.push_back({l, r});
                acc += lr.back().sc - lr.back().fr;

                ans += acc;
                // cout << i << ' ' << j << ' ' << acc << '\n';
            }
        }

        cout << ans << '\n';
    }
}