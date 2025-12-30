#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define sz(x) (int)(x).size()

ll power(ll x, ll y, const ll mod) {
    if (!y) return 1;
    ll res = power(x, y / 2, mod);
    return res * res % mod * (y & 1 ? x : 1) % mod;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n, m, _p;
        cin >> n >> m >> _p;
    
        const int mod = _p;

        vector<ll> pow_m_inv(n + 1);
        pow_m_inv[0] = 1;
        pow_m_inv[1] = power(m, mod - 2, mod);
        for (int i = 2; i <= n; i++) {
            pow_m_inv[i] = pow_m_inv[1] * pow_m_inv[i - 1] % mod;
        }

        vector<ll> e1_o(n / 2 + 1), e1_e(n / 2 + 1);

        e1_o[0] = 1;
        for (int r = 1; r <= n / 2; r++) {
            e1_o[r] = (e1_o[r - 1] + pow_m_inv[r]) % mod;
            e1_e[r] = (e1_e[r - 1] + pow_m_inv[r]) % mod;
        }

        ll ans = 0;

        ll acc = 0;
        for (int i = 1; i <= 2 * n - 1; i++) {
            int r = min(i / 2, (2 * n - i) / 2);
            
            const ll e1 = (i & 1 ? e1_o[r] : e1_e[r]);
            ans = (ans + 2 * acc % mod * e1) % mod;
            acc = (acc + e1) % mod;
        }

        vector<ll> e2_o(n / 2 + 1), e2_e(n / 2 + 1);

        for (ll r = 0; r <= n / 2; r++) {
            {
                ll res_o = 1;
                res_o = res_o * pow_m_inv[r] % mod;
                res_o = res_o * (2 * r + 1) % mod;

                e2_o[r] = res_o % mod;
            }
            if (r >= 1) {
                ll res_e = 1;
                res_e = res_e * pow_m_inv[r] % mod;
                res_e = res_e * (2 * r - 1) % mod;

                e2_e[r] = res_e % mod;
            }

            if (r >= 1) {
                e2_o[r] = (e2_o[r] + e2_o[r - 1]) % mod;
                e2_e[r] = (e2_e[r] + e2_e[r - 1]) % mod;
            }
        }

        for (int i = 1; i <= 2 * n - 1; i++) {
            int r = min(i / 2, (2 * n - i) / 2);
            
            const ll e2 = (i & 1 ? e2_o[r] : e2_e[r]);
            ans = (ans + e2) % mod;
        }

        cout << ans << '\n';
    }
}
