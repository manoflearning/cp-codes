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

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// // what: maintain a sorted set with order statistics (k-th / count < x) for distinct keys.
// // time: insert/erase/order_of_key/find_by_order O(log n); memory: O(n)
// // constraint: GNU pbds only.
// // usage: oset s; s.order_of_key(x); s.find_by_order(k);
// using oset = tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>;

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

        for (int i = 1; i <= n; i++) {
            a[i] = lower_bound(all(cc), a[i]) - cc.begin();
        }

        vector<int> ord(n);
        iota(all(ord), 1);
        sort(all(ord), [&](int i, int j) {
            return a[i] > a[j];
        });

        vector<ll> dp(n + 2);
        set<int> stu, std;

        stu.insert(n + 1);
        std.insert(n + 1);
        for (int i : ord) std.insert(i);

        ll ans = 0;

        for (int i : ord) {
            stu.insert(i);
            std.erase(i);

            int k = *stu.upper_bound(i);
            ll l = k - i - 1;
            int p = *std.lower_bound(k);
            
            dp[i] += l * (l + 1) / 2;
            dp[i] += l * (p - k);
            dp[i] += (l + 1) * ((n - k + 1) - (p - k));
            dp[i] += dp[k];

            ans += dp[i];
            // cout << i << ' ' << dp[i] << '\n';
        }

        cout << ans << '\n';
    }
}