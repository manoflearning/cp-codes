#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

constexpr int MOD = 1'000'000'007;

int n, m;
vector<int> a;
vector<vector<ll>> dp;

ll pow_mod(ll x, ll y) {
    if (!y) return 1;
    ll res = pow_mod(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    cin >> n >> m;
    a.assign(n, 0);
    for (auto &i : a) cin >> i;

    // base case
    dp.assign(m + 2, vector<ll>(m + 2, 0));
    for (int i = 1; i <= m; i++) {
        dp[i][i] = 0;
        dp[i][m + 1] = m + 1 - i;
    }

    // inductive step
    const ll inv2 = pow_mod(2, MOD - 2);

    for (int i = m; i >= 1; i--) {
        for (int j = m; j > i; j--) {
            dp[i][j] = (1 + dp[i + 1][j] + dp[i][j + 1]) * inv2 % MOD;

            if (j == m + 1) break;
        }
    }

    ll ans = 0;
    a.resize(n + 1);
    a[n] = m + 1;
    for (int i = 0; i + 1 <= n; i++) {
        ans = (ans + dp[a[i]][a[i + 1]]) % MOD;
    }
    cout << ans;
}
