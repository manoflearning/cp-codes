#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int MOD = 1e9 + 7;

// what: linear sieve for lp/primes/mu/phi with factorization helpers.
// time: O(n) build; O(log x) factor; memory: O(n)
// constraint: factor(x) requires 1 <= x <= n.
// usage: lin_sieve sv(n); auto fc=sv.factor_cnt(x); int mu=sv.mu[x];
struct lin_sieve {
    int n;
    vector<int> lp, primes, mu, phi;

    lin_sieve(int n_ = 0) {
        if (n_ >= 0) init(n_);
    }
    void init(int n_) {
        // goal: fill lp/primes/mu/phi for [0..n]
        n = n_;
        lp.assign(n + 1, 0);
        primes.clear();
        mu.assign(n + 1, 0);
        phi.assign(n + 1, 0);
        if (n >= 1) mu[1] = 1, phi[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (!lp[i]) {
                lp[i] = i;
                primes.push_back(i);
                mu[i] = -1;
                phi[i] = i - 1;
            }
            for (int p : primes) {
                ll v = 1LL * p * i;
                if (v > n) break;
                lp[v] = p;
                if (p == lp[i]) {
                    mu[v] = 0;
                    phi[v] = phi[i] * p;
                    break;
                }
                mu[v] = -mu[i];
                phi[v] = phi[i] * (p - 1);
            }
        }
    }
    bool is_prime(int x) const { return x >= 2 && x <= n && lp[x] == x; }
    vector<int> factor(int x) const {
        // result: prime factors of x (with repetition), in nondecreasing order
        vector<int> ret;
        while (x > 1) {
            int p = lp[x];
            ret.push_back(p);
            x /= p;
        }
        return ret;
    }
    vector<pii> factor_cnt(int x) const {
        // result: {{p, e}} s.t. x = prod p^e, increasing p
        vector<pii> ret;
        while (x > 1) {
            int p = lp[x];
            int e = 0;
            while (x % p == 0) x /= p, e++;
            ret.push_back({p, e});
        }
        return ret;
    }
};

ll pow_mod(ll x, ll y) {
    if (!y) return 1;
    const ll res = pow_mod(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    lin_sieve ls(202020);

    int tc; cin >> tc;
    while (tc--) {
        int n, c;
        string s;
        cin >> n >> c >> s;

        s = "*" + s;
        if (s[1] == '0' || s[n] == '0') {
            cout << -1 << '\n';
            continue;
        }

        ll ans = 2;
        
        vector<int> mp(n + 1);
        mp[2]++;
        for (int i = 2; i <= n - 1; i++) {
            if (s[i] == '1') {
                ans = ans * 2 % MOD;
                mp[2]++;
            } else {
                ans = ans * (i - 1) % MOD;
                vector<int> ps = ls.factor(i - 1);
                for (auto &p : ps) {
                    mp[p]++;
                }
            }
        }

        for (int k = 2; k <= n; k++) {
            // if (mp[k]) cout << k << ' ' << mp[k] << '\n';
            while (c % k == 0 && mp[k] > 0) {
                c /= k, mp[k]--;
                // cout << v << ' ' << c << '\n';
            }
        }
        // cout << c << ' ';

        if (c == 1) {
            cout << -1 << '\n';
        } else {
            cout << ans << '\n';
        }
    }
}
