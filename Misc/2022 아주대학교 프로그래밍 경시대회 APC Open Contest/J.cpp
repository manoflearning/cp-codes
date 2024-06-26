#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1e9 + 7;

const int MAXN = 202020;

ll fac[MAXN], inv[MAXN], facInv[MAXN];

ll binom(int n, int r) {
	return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
}

void pre() {
    // Preprocessing in O(N)
	fac[0] = fac[1] = inv[1] = 1;
	facInv[0] = facInv[1] = 1;
	for (int i = 2; i < MAXN; i++) {
		fac[i] = i * fac[i - 1] % MOD;
		inv[i] = -(MOD / i) * inv[MOD % i] % MOD;
		if (inv[i] < 0) inv[i] += MOD;
		facInv[i] = facInv[i - 1] * inv[i] % MOD;
	}
}

int n, k;

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	pre();

    cin >> n >> k;

    ll sum = 0;
    for (int i = 0; i <= k; i++) {
        ll res = binom(k, i) * binom(n - i, k - i) % MOD * fac[k - i] % MOD;;
        if (i & 1) sum = (sum - res + MOD) % MOD;
        else sum = (sum + res) % MOD;
    }

    sum = sum * binom(n, k) % MOD * fac[k] % MOD;
    sum = (sum + MOD) % MOD;

    cout << sum;

	return 0;
}