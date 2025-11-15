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
constexpr ll dx[] = {1, -1, 1, -1};
constexpr ll dy[] = {1, 1, -1, -1};

constexpr int K = 2020;
constexpr int MOD = 998'244'353;

int n, k;
ll dp[K][K];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k;
    n = min(n, k);
    
    // base case
    for (int i = 1; i <= k; i++) {
        dp[1][i] = 1;
    }

    // inductive step
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            ll now = i * j;

            for (ll prv = now / (i - 1) * (i - 1); prv >= (i - 1); prv -= (i - 1)) {
                if (k < now - prv) break;
                if (now == prv) continue;

                int cnt = prv / (i - 1);
                if (cnt <= k) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][cnt]) % MOD;
                }
            }

            // cout << "i = " << i << ", j = " << j;
            // cout << ", dp[i][j] = " << dp[i][j] << '\n';
        }
    }

    ll ans = 0;
    for (int i = 1; i <= k; i++) {
        ans = (ans + dp[n][i]) % MOD;
    }

    cout << ans;
}