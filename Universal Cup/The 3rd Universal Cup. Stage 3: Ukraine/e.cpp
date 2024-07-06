#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MOD = 998244353;

const int MAXN = 4040404;
ll fac[MAXN], inv[MAXN], facInv[MAXN];
ll binom(int n, int r) {
	return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
}

ll power(ll x, ll y) {
    if (y == 0) return 1;
    if (y == 1) return x;
    ll res = power(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

ll dp[101][101];

ll naive(ll n, ll m) {
    ll& ret = dp[n][m];
    if (ret != -1) return ret;
    if (n == 1) return ret = m * m % MOD;
    if (m == 1) return ret = 1;
    
    ret = 0;
    ret = (ret + 2 * power(m, n) % MOD + MOD - 1) % MOD;
    for (int k = 0; k <= n - 1; k++) {
        ret = (ret + binom(n, k) * naive(n - k, m - 1) % MOD) % MOD;
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

    memset(dp, -1, sizeof(dp));

    // Preprocessing in O(N)
	fac[0] = fac[1] = inv[1] = 1;
	facInv[0] = facInv[1] = 1;
	for (int i = 2; i < MAXN; i++) {
		fac[i] = i * fac[i - 1] % MOD;
		inv[i] = -(MOD / i) * inv[MOD % i] % MOD;
		if (inv[i] < 0) inv[i] += MOD;
		facInv[i] = facInv[i - 1] * inv[i] % MOD;
	}

    ll n, m;
    cin >> n >> m;

    ll ans = 0;
    for (ll i = 1; i <= m; i++) {
        ans = (ans + 2 * power(i, n) % MOD + MOD - 1) % MOD;
        ans = (ans + power(i - 1, 2) * n % MOD) % MOD;
    }

    cout << ans;

    // for (ll n = 1; n <= 10; n++) {
    //     // cout << "n is: " << n << ", ";
    //     // cout << "ans = " << naive(n, 2) << ' ';
    //     cout << naive(n, 2) << ", ";
    // }
    // cout << '\n';

    // cout << naive(n, m);
}