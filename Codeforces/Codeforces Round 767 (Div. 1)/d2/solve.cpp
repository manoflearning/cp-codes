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
constexpr int N = 1010101;

ll pow_mod(ll x, ll y) {
    if (!y) return 1;
    const ll res = pow_mod(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

array<ll, N> fac, ifac;

ll ncr(ll n, ll r) {
    if (r < 0 || n < r) return 0;
    ll ret = 1;
    ret = ret * fac[n] % MOD;
    ret = ret * ifac[r] % MOD;
    ret = ret * ifac[n - r] % MOD;
    return ret;
}

int n, m;
ll k;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    fac[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = i * fac[i - 1] % MOD;
    }
    ifac[N - 1] = pow_mod(fac[N - 1], MOD - 2);
    for (int i = N - 1; i >= 1; i--) {
        ifac[i - 1] = i * ifac[i] % MOD;
    }

    int tc; cin >> tc;
    while (tc--) {
        cin >> n >> m >> k;

        ll ans = 0;

        if (n == m) {
            ans = m * k % MOD;
        } else {
            ll pow_inv2 = pow_mod(pow_mod(2, n), MOD - 2);

            for (int i = 1; i <= m; i++) {
                pow_inv2 = pow_inv2 * 2 % MOD;
                
                ll res = 1;
                res = res * i * k % MOD;
                const ll comb = ncr(n - i - 1, m - i);
                res = res * comb % MOD;
                res = res * pow_inv2 % MOD;

                ans = (ans + res) % MOD;
            }
        }

        cout << ans << '\n';
    }
}
