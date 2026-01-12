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
        for (int i = 1; i <= n; i++) {
            fac[i] = fac[i - 1] * i % MOD;
        }
        ifac[n] = pow_mod(fac[n], MOD - 2);
        for (int i = n; i >= 1; i--) {
            ifac[i - 1] = ifac[i] * i % MOD;
        }
    }
    ll ncr(int n_, int r) const {
        if (r < 0 || n_ < r || n_ > n) return 0;
        ll ret = fac[n_] * ifac[r] % MOD;
        ret = ret * ifac[n_ - r] % MOD;
        return ret;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> a(n);
        for (auto &i : a) cin >> i;

        bool yes = 1;
        for (int i = (n + 1) / 2; i < n; i++) {
            if (a[i]) yes = 0;
        }

        if (!yes) {
            cout << 0 << '\n';
            continue;
        }

        comb_mod cb;
        cb.init(n);

        ll ans = 1;

        int rem = 0;
        for (int i = (n - 1) / 2; i >= 0; i--) {
            rem += (i == (n - 1) / 2 ? (n & 1 ? 1 : 2) : 2);

            ans = ans * cb.ncr(rem, a[i]) % MOD;
            rem -= a[i];
        }
        ans *= (rem == 0);

        cout << ans << '\n';
    }
}