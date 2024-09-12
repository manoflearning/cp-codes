#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1e9 + 7;
const int MAXN = 121;

ll fac[MAXN], inv[MAXN], facInv[MAXN];
ll binom(int n, int r) {
	return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
}

ll f(int n, int m, int p) {
    ll ret = 1;
    for (int i = 0; i < min(m + 1, p); i++) {
        ret = ret * (n - i) % MOD;
    }
    for (int i = m + 1; i < p; i++) {
        ret = ret * (n - m) % MOD;
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    // Preprocessing in O(N)
	fac[0] = fac[1] = inv[1] = 1;
	facInv[0] = facInv[1] = 1;
	for (int i = 2; i < MAXN; i++) {
		fac[i] = i * fac[i - 1] % MOD;
		inv[i] = -(MOD / i) * inv[MOD % i] % MOD;
		if (inv[i] < 0) inv[i] += MOD;
		facInv[i] = facInv[i - 1] * inv[i] % MOD;
	}

    int n, m, p;
    cin >> n >> m >> p;

    ll ans = 0;
    for (int i = n; i >= 1; i--) {
        ans += (i % 2 == n % 2 ? 1 : -1) * binom(n, i) * f(i, m, p) % MOD;
        ans %= MOD;
    }

    cout << (ans + MOD) % MOD;
}
