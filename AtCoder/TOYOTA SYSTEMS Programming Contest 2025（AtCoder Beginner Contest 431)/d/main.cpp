#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr ll INF = 1e18;
constexpr int MOD = 1e9 + 7;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    int n; cin >> n;

    vector<ll> w(n), h(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> h[i] >> b[i];
    }

    constexpr int base = 252525;
    vector<ll> dp(2 * base, -INF);
    
    dp[base] = 0;

    for (int i = 0; i < n; i++) {
        vector<ll> nxt(2 * base, -INF);
        for (int j = 0; j < base * 2; j++) {
            if (dp[j] == -INF) continue;

            if (j - w[i] >= 0) {
                // cout << j - w[i] << ' ' << dp[j] + h[i] << '\n';
                nxt[j - w[i]] = max(nxt[j - w[i]], dp[j] + h[i]);
            }
            if (j + w[i] < 2 * base) {
                // cout << j + w[i] << ' ' << dp[j] + b[i] << '\n';
                nxt[j + w[i]] = max(nxt[j + w[i]], dp[j] + b[i]);
            }
        }
        dp = nxt;
    }

    ll ans = 0;
    for (int i = base; i < 2 * base; i++) {
        if (dp[i] == -INF) continue;
        // cout << i << ' ' << dp[i] << '\n';
        ans = max(ans, dp[i]);
    }

    cout << ans;
}