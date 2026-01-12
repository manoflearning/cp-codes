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

ll pow_mod(ll x, ll y) {
    if (!y) return 1;
    ll res = pow_mod(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

struct comb_mod {
    int n;
    vector<ll> fac, ifac;
    void init(int n_) {
        n = n_;
        fac.assign(n + 1, 1);
        ifac.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % MOD;
        ifac[n] = pow_mod(fac[n], MOD - 2);
        for (int i = n; i >= 1; i--) ifac[i - 1] = ifac[i] * i % MOD;
    }
    ll ncr(int n_, int r) const {
        if (r < 0 || n_ < r || n_ > n) return 0;
        ll ret = fac[n_] * ifac[r] % MOD;
        ret = ret * ifac[n_ - r] % MOD;
        return ret;
    }
    ll nhr(int n_, int r) const { return ncr(n_ + r - 1, r); }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<ll> a(n + 2);
        for (int i = 1; i <= n; i++) cin >> a[i];

        comb_mod cb;
        cb.init(2 * n);

        vector<ll> ps(n + 3);

        auto add = [&](int i, int j, int k, int l, ll val) {
            ps[i] += val;
            ps[j] -= val;

            ps[k] -= val;
            ps[l] += val;
        };

        for (int l = 1; l <= n; l++) {
            if (l > 1) {
                for (int x = 0; x <= 1; x++) {
                    for (int y = 0; y <= 1; y++) {
                        const ll avg = (n - x - y) * pow_mod(l, MOD - 2) % MOD;
                        if ((n - x - y - l) & 1) continue;

                        const ll cnt = cb.nhr(l, (n - x - y - l) / 2);

                        add(1, 2, n - l + 2, n - l + 3, cnt * (avg + x) % MOD);
                        add(2, l, n - l + 3, n + 1, cnt * avg % MOD);
                        add(l, l + 1, n + 1, n + 2, cnt * (avg + y) % MOD);
                    }
                }
            } else {
                const ll cnt = 1;
                ps[1] += cnt * n % MOD;
                ps[l + 1] -= cnt * n % MOD;
                ps[n - l + 2] -= cnt * n % MOD;
            }
        }

        for (int i = 1; i <= n; i++) {
            ps[i] = (ps[i] + ps[i - 1]) % MOD;
            if (ps[i] < 0) ps[i] += MOD;
        }

        for (int i = 1; i <= n; i++) {
            ps[i] = (ps[i] + ps[i - 1]) % MOD;
            // cout << i << ' ' << ps[i] << '\n';
        }

        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            ans = (ans + a[i] * ps[i]) % MOD;
        }
        cout << ans << '\n';
    }
}
