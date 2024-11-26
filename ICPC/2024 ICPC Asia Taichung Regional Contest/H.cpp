#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 998244353;
const int MAXN = 1010101;

ll fac[MAXN], inv[MAXN], facInv[MAXN];
ll binom(int n, int r) {
  return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
}

ll n, k;
ll dp[MAXN][2], pdp[MAXN][2];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // Preprocessing in O(N)
    fac[0] = fac[1] = inv[1] = 1;
    facInv[0] = facInv[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        fac[i] = i * fac[i - 1] % MOD;
        inv[i] = -(MOD / i) * inv[MOD % i] % MOD;
        if (inv[i] < 0) inv[i] += MOD;
        facInv[i] = facInv[i - 1] * inv[i] % MOD;
    }

    cin >> n >> k;

    if (n == 1) {
        cout << 1;
        exit(0);
    }

    // base case
    dp[0][0] = dp[0][1] = 1;
    pdp[0][0] = pdp[0][1] = 1;

    // inductive step
    for (int i = 1; i <= n - 1; i++) {
        int j = max(-1ll, i - k);

        dp[i][0] = (pdp[i - 1][1] - (j >= 0 ? pdp[j][1] : 0) + MOD) % MOD;
        dp[i][1] = (pdp[i - 1][0] - (j >= 0 ? pdp[j][0] : 0) + MOD) % MOD;

        pdp[i][0] = (dp[i][0] + pdp[i - 1][0]) % MOD;
        pdp[i][1] = (dp[i][1] + pdp[i - 1][1]) % MOD;
    }

    ll ans = 1;
    for (int i = 1; i <= n - 1; i++) {
        ans = (ans + (dp[i][0] + dp[i][1]) * binom(n - 1, i) % MOD) % MOD;
    }

    cout << ans;
}
