#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

constexpr int MOD = 1e9 + 7;

ll pow_mod(ll x, ll y) {
    if (!y) return 1;
    const ll res = pow_mod(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

int n, m;
ll k;
vector<vector<ll>> dp;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        cin >> n >> m >> k;

        dp.assign(m + 1, vector<ll>(n - m + 1));

        // base case
        for (int p = 1; p <= m; p++) {
            dp[p][0] = (k + dp[p - 1][0]) % MOD;
        }
        for (int q = 1; q <= n - m; q++) {
            dp[0][q] = 0;
        }

        // inductive step
        const ll inv2 = pow_mod(2, MOD - 2);
        for (int p = 1; p <= m; p++) {
            for (int q = 1; q <= n - m; q++) {
                dp[p][q] = (dp[p][q - 1] + dp[p - 1][q]) * inv2 % MOD;
            }
        }

        cout << dp[m][n - m] << '\n';
    }
}
