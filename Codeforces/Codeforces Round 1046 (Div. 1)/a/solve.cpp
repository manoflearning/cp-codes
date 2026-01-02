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

constexpr int INF = 1e9 + 7;

// what: maintain a sorted set with order statistics (k-th / count < x) for distinct keys.
// time: insert/erase/order_of_key/find_by_order O(log n); memory: O(n)
// constraint: GNU pbds only.
// usage: oset s; s.order_of_key(x); s.find_by_order(k);
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using oset = tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    
    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];

        vector<int> dp(n + 1, -INF);
        
        // base case
        dp[0] = 0;
        
        // inductive step
        vector<oset> idxs(n + 1);
        for (int i = 1; i <= n; i++) {
            dp[i] = dp[i - 1];

            idxs[a[i]].insert(i);
            if (sz(idxs[a[i]]) >= a[i]) {
                auto it = idxs[a[i]].find_by_order(sz(idxs[a[i]]) - a[i]);
                dp[i] = max(dp[i], dp[*it - 1] + a[i]);
            }
        }

        cout << dp[n] << '\n';
    }
}