#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

array<ll, 4> f(const vector<pll>& arr, ll l, ll r) {
    if (sz(arr) == 0) return {0ll, 0ll, 0ll, 0ll};

    array<ll, 4> ret = {(ll)1e18, (ll)1e18, (ll)1e18, (ll)1e18};
    for (int i = 0; i <= sz(arr); i++) {
        ll val_l = (i == 0 ? 0 : arr[i - 1].fr - l);
        ll val_r = (i == sz(arr) ? 0 : r - arr[i].sc);
        ret[0] = min(ret[0], val_l + val_r);
        ret[1] = min(ret[1], 2 * val_l + val_r);
        ret[2] = min(ret[2], val_l + 2 * val_r);
        ret[3] = min(ret[3], 2 * val_l + 2 * val_r);
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;

        vector<ll> a(n);
        for (auto &i : a) cin >> i;
        sort(all(a));

        vector<pll> b(m);
        for (auto &[l, r] : b) cin >> l >> r;

        // remove initially visited intervals
        {
            vector<pll> tmp;
            for (auto [l, r] : b) {
                int idx = lower_bound(all(a), l) - a.begin();
                if (idx == sz(a) || r < a[idx]) {
                    tmp.push_back({l, r});
                }
            }
            b = tmp;
        }

        // remove all the intervals which contain the other
        {
            sort(all(b), [](const pll& p1, const pll& p2) {
                if (p1.fr ^ p2.fr) return p1.fr < p2.fr;
                else return p1.sc > p2.sc;
            });

            vector<pll> tmp;
            for (auto [l, r] : b) {
                while (!tmp.empty() && r <= tmp.back().sc) {
                    tmp.pop_back();
                }
                tmp.push_back({l, r});
            }
            b = tmp;
        }

        // calculate the "gap"
        vector<vector<pll>> gap(n + 1);
        {
            int idx = 0; // (a[idx - 1], a[idx])
            for (auto [l, r] : b) {
                while (idx < n) {
                    if (a[idx] < l) idx++;
                    else break;
                }
                gap[idx].push_back({l, r});
            }

            // DEBUG
            // for (int i = 0; i <= n; i++) {
            //     if (i == 0) {
            //         cout << "gap = (-inf, " << a[i] << ")\n";
            //     } else if (i == n) {
            //         cout << "gap = (" << a[i - 1] << ", inf)\n";
            //     } else {
            //         cout << "gap = (" << a[i - 1] << ", " << a[i] << ")\n";
            //     }
            //     cout << "intervals:\n";
            //     for (auto &[l, r] : gap[i]) {
            //         cout << l << ' ' << r << '\n';
            //     }
            //     cout << '\n';
            // }
        }

        // calculate dp table
        vector<array<ll, 4>> dp(n + 1);
        for (int i = 0; i <= n; i++) {
            array<ll, 4> res = f(gap[i], (0 < i ? a[i - 1] : -1e15), (i < n ? a[i] : +1e15));

            if (i == 0) {
                dp[i] = res;
            } else {
                dp[i][0] = min(dp[i - 1][2] + res[0], dp[i - 1][3] + res[0]);
                dp[i][1] = min(dp[i - 1][0] + res[1], dp[i - 1][1] + res[1]);
                dp[i][2] = min(dp[i - 1][2] + res[2], dp[i - 1][3] + res[2]);
                dp[i][3] = min(dp[i - 1][0] + res[3], dp[i - 1][1] + res[3]);
            }
        }

        cout << min({dp[n][0], dp[n][1], dp[n][2], dp[n][3]}) << '\n';
    }
}
