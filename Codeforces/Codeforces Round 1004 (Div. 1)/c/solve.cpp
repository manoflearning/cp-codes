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

        vector<int> a(n + 1), pref(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            pref[i] = (a[i] ^ pref[i - 1]);
        }

        map<int, ll> dp;
        
        // base case
        dp[0] = 1;

        // inductive step
        for (int i = 1; i <= n; i++) {
            dp[pref[i - 1]] = 3 * dp[pref[i - 1]];
            dp[pref[i - 1]] %= MOD;
            dp[pref[i - 1]] += 2 * dp[pref[i]];
            dp[pref[i - 1]] %= MOD;
            // dp[pref[i]] += dp[pref[i]];
            // dp[pref[i]] %= MOD;
        }

        ll ans = 0;
        for (auto &[_, v] : dp) {
            ans = (ans + v) % MOD;
        }
        cout << ans << '\n';
    }
}
