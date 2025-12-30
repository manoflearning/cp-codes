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

ll power(ll x, ll y, const ll mod) {
    if (!y) return 1;
    ll res = power(x, y >> 1, mod);
    return res * res % mod * (y & 1 ? x : 1) % mod;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        ll n, m, _p;
        cin >> n >> m >> _p;

        const ll mod = _p;

        const ll m_inv = power(m, mod - 2, mod);

        vector<ll> pow_m_inv(n + 1);
        vector<ll> psum(n + 1), psum2(n + 1);

        pow_m_inv[0] = 1;
        psum[0] = 1;
        for (int i = 1; i <= n; i++) {
            pow_m_inv[i] = m_inv * pow_m_inv[i - 1] % mod;
            psum[i] = (pow_m_inv[i] + psum[i - 1]) % mod;
            psum2[i] = (i * pow_m_inv[i] + psum2[i - 1]) % mod;
        }

        vector<ll> a(2 * n + 1), b(2 * n + 1);

        ll sum_a = 0;
        for (int i = 3; i <= 2 * n; i += 2) {
            ll r = min<ll>(i / 2, n - i / 2);
            a[i] = psum[r] - 1;
            sum_a = (sum_a + a[i]) % mod;

            b[i] = (2 * psum2[r] - psum[r] + 1 + mod) % mod;
        }
        for (int i = 2; i <= 2 * n; i += 2) {
            ll r = min<ll>(i / 2, n - i / 2 + 1) - 1;
            a[i] = psum[r];
            sum_a = (sum_a + a[i]) % mod;

            b[i] = (2 * psum2[r] + psum[r]) % mod;
        }

        ll ans = 0;
        ans += sum_a * sum_a % mod;
        ans %= mod;
        for (int i = 2; i <= 2 * n; i++) {
            ans += mod - power(a[i], 2, mod);
            ans %= mod;
            ans += b[i];
            ans %= mod;
        }

        cout << ans << '\n';
    }
}
