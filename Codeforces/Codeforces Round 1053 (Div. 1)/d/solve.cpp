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

constexpr int MOD = 998'244'353;
constexpr int N = 202020;

ll fac[N], inv[N], facInv[N];
ll binom(int n, int r) {
    return fac[n] * facInv[r] % MOD * facInv[n - r] % MOD;
}

ll power(ll x, ll y) {
    if (!y) return 1;
    ll res = power(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    // Preprocessing in O(N)
    fac[0] = fac[1] = inv[1] = 1;
    facInv[0] = facInv[1] = 1;
    for (int i = 2; i < N; i++) {
        fac[i] = i * fac[i - 1] % MOD;
        inv[i] = -(MOD / i) * inv[MOD % i] % MOD;
        if (inv[i] < 0) inv[i] += MOD;
        facInv[i] = facInv[i - 1] * inv[i] % MOD;
    }
  
    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<ll> a(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];

        vector<ll> ps(n + 2), pps(n + 2);
        for (int i = 1; i <= n; i++) {
            ps[i] = (a[i] + ps[i - 1]) % MOD;
        }
        for (int i = 1; i <= n; i++) {
            pps[i] = (ps[i] + pps[i - 1]) % MOD;
        }

        ll ans = 0;

        for (int k = 2; k <= n; k++) {
            for (int x = 1; x <= 2; x++) {
                for (int y = 1; y <= 2; y++) {
                    ll s = n - (x + y + (k - 2));
                    if (s < 0 || (s & 1)) continue;

                    ll sdiv = s * power(2 * k, MOD - 2) % MOD;

                    const ll avg = (2 * sdiv + 1) % MOD;
                    const ll ways = binom(k + s / 2 - 1, s / 2);

                    ll res = 0;
                    res = (res + (pps[n] - pps[k - 1] - pps[n - k]) * avg) % MOD;
                    res = (res + MOD) % MOD;

                    if (x == 2) {
                        res = (res + ps[n - k + 1]) % MOD;
                        res = (res + MOD) % MOD;
                    }
                    if (y == 2) {
                        res = (res + ps[n] - ps[k - 1]) % MOD;
                        res = (res + MOD) % MOD;
                    }

                    res = res * ways % MOD;

                    ans = (ans + res) % MOD;
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            ans = (ans + n * a[i]) % MOD;
        }

        cout << ans << '\n';
    }
}
