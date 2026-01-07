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

constexpr int MOD = 1e9 + 7;
constexpr int N = 202020;

// what: fast modular exponentiation (binary exponentiation).
// time: O(log e); memory: O(1)
// constraint: mod > 0.
// usage: ll p=pow_mod(a,e,mod);
inline ll pow_mod(ll a, ll e) {
    ll r = 1 % MOD;
    a %= MOD;
    if (a < 0) a += MOD;
    while (e) {
        if (e & 1) r = (ll)((__int128)r * a % MOD);
        a = (ll)((__int128)a * a % MOD);
        e >>= 1;
    }
    return r;
}

// what: compute nCr mod p using factorials and inverse factorials.
// time: O(n) init, O(1) query; memory: O(n)
// constraint: mod is prime; 0 <= n <= precomputed N.
// usage: comb_mod cb; cb.init(n, mod); ll v=cb.ncr(n, r);
struct comb_mod {
    int n;
    vector<ll> fac, ifac;

    void init(int n_) {
        // goal: precompute fac/ifac up to n.
        n = n_;
        fac.assign(n + 1, 1);
        ifac.assign(n + 1, 1);

        ll deb = 1;
        for (int i = 1; i <= n; i++) {
            deb = deb * i % MOD;
            fac[i] = (ll)((__int128)fac[i - 1] * i % MOD);
        }
        ifac[n] = pow_mod(fac[n], MOD - 2);
        for (int i = n; i >= 1; i--) {
            ifac[i - 1] = (ll)((__int128)ifac[i] * i % MOD);
        }
    }
    ll ncr(int n_, int r) const {
        if (r < 0 || n_ < r || n_ > n) return 0;
        ll ret = (ll)((__int128)fac[n_] * ifac[r] % MOD);
        ret = (ll)((__int128)ret * ifac[n_ - r] % MOD);
        return ret;
    }
};

int n, k;
vector<vector<int>> t;
vector<ll> dep, siz;
ll sum = 0;
comb_mod cb;

void dfs(int v, int prv) {
    dep[v] = dep[prv] + 1;
    siz[v] = 1;

    ll acc = 0;
    for (auto &i : t[v]) {
        if (i == prv) continue;

        dfs(i, v);

        sum -= 2 * acc * cb.ncr(siz[i], k / 2) % MOD * (dep[v] - 1) % MOD;
        sum -= acc * cb.ncr(siz[i], k / 2) % MOD;
        sum %= MOD;

        siz[v] += siz[i];
        acc = (acc + cb.ncr(siz[i], k / 2)) % MOD;
    }

    ll acc2 = 0;
    for (auto &i : t[v]) {
        if (i == prv) continue;

        sum -= cb.ncr(siz[i], k / 2) * cb.ncr(n - siz[v], k / 2 - 1) % MOD * (dep[v] - 1) % MOD;
        acc2 = (acc2 + cb.ncr(siz[i], k / 2)) % MOD;
        sum %= MOD;
    }

    sum += (cb.ncr(siz[v], k / 2) - acc2 + MOD) % MOD * cb.ncr(n - siz[v], k / 2) % MOD * dep[v] % MOD;
    sum %= MOD;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cb.init(N);

    cin >> n >> k;

    t.assign(n + 1, vector<int>());
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        t[u].push_back(v);
        t[v].push_back(u);
    }

    ll ans = 1;
    if (k & 1) {
        ans = 1;
    } else {
        dep.assign(n + 1, 0);
        siz.assign(n + 1, 0);
        sum = 0;
        dfs(1, 0);
        sum = (sum + MOD) % MOD;

        ans = sum * pow_mod(cb.ncr(n, k), MOD - 2) % MOD;
    }

    cout << ans << '\n';
}
