#pragma GCC optimize("O3")
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

constexpr int MOD = 1'000'000'007;
constexpr int INF = 1'000'000'007;

// what: fast modular exponentiation (binary exponentiation).
// time: O(log e); memory: O(1)
// constraint: mod > 0.
// usage: ll p=pow_mod(a,e,mod);
inline ll pow_mod(ll a, ll e, ll mod) {
    ll r = 1 % mod;
    a %= mod;
    if (a < 0) a += mod;
    while (e) {
        if (e & 1) r = (ll)((__int128)r * a % mod);
        a = (ll)((__int128)a * a % mod);
        e >>= 1;
    }
    return r;
}

// what: gcd/egcd/inverse helpers and modular exponentiation.
// time: O(log n); memory: O(1)
// constraint: works for any ll.
// usage: auto eg=euclid::egcd(a,b); ll inv=euclid::inv_mod(a,mod);
struct euclid {
    static ll gcd(ll a, ll b) {
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        while (b) {
            ll t = a % b;
            a = b;
            b = t;
        }
        return a;
    }
    static ll lcm(ll a, ll b) {
        if (!a || !b) return 0;
        ll v = a / gcd(a, b) * b;
        if (v < 0) v = -v;
        return v;
    }
    static pair<pll, ll> egcd(ll a, ll b) {
        // result: {{x, y}, g} s.t. a*x + b*y = g = gcd(a, b)
        ll s = 0, os = 1;
        ll t = 1, ot = 0;
        ll r = b, orr = a;
        while (r) {
            ll q = orr / r;
            ll nr = orr - q * r;
            orr = r;
            r = nr;
            ll ns = os - q * s;
            os = s;
            s = ns;
            ll nt = ot - q * t;
            ot = t;
            t = nt;
        }
        if (orr < 0) {
            orr = -orr;
            os = -os;
            ot = -ot;
        }
        return {{os, ot}, orr};
    }
    static ll inv_mod(ll a, ll mod) {
        // result: x in [0, mod) s.t. a*x = 1 (mod mod), or -1 if not invertible.
        a %= mod;
        if (a < 0) a += mod;
        auto res = egcd(a, mod);
        if (res.sc != 1) return -1;
        ll x = res.fr.fr % mod;
        if (x < 0) x += mod;
        return x;
    }
    static ll lin_cong(ll a, ll b, ll mod) {
        // what: solve linear congruence a*x = b (mod mod).
        // result: one x in [0, mod) if exists, else -1.
        auto res = egcd(a, mod);
        ll g = res.sc;
        if (b % g) return -1;
        ll x = (ll)((__int128)res.fr.fr * (b / g) % mod);
        if (x < 0) x += mod;
        return x;
    }
};

// what: compute nCr mod p using factorials and inverse factorials.
// time: O(n) init, O(1) query; memory: O(n)
// constraint: mod is prime; 0 <= n <= precomputed N.
// usage: comb_mod cb; cb.init(n, mod); ll v=cb.ncr(n, r);
struct comb_mod {
    int n;
    ll mod;
    vector<ll> fac, ifac;

    void init(int n_, ll mod_) {
        // goal: precompute fac/ifac up to n.
        n = n_;
        mod = mod_;
        fac.assign(n + 1, 1);
        ifac.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) fac[i] = (ll)((__int128)fac[i - 1] * i % mod);
        ifac[n] = pow_mod(fac[n], mod - 2, mod);
        for (int i = n; i >= 1; i--) ifac[i - 1] = (ll)((__int128)ifac[i] * i % mod);
    }
    ll ncr(int n_, int r) const {
        if (r < 0 || n_ < r || n_ > n) return 0;
        ll ret = (ll)((__int128)fac[n_] * ifac[r] % mod);
        ret = (ll)((__int128)ret * ifac[n_ - r] % mod);
        return ret;
    }
};

// what: precompute Catalan numbers modulo a prime.
// time: O(n) init, O(1) query; memory: O(n)
// constraint: mod is prime; n < mod (so inv(n+1) exists).
// usage: catalan_mod ct; ct.init(n, mod); ll v=ct.catalan(k);
struct catalan_mod {
    comb_mod cb;
    ll mod;

    void init(int n, ll mod_) {
        // goal: precompute factorials up to 2n.
        mod = mod_;
        cb.init(2 * n, mod);
    }
    ll catalan(int n) const {
        ll ret = cb.ncr(2 * n, n);
        ll inv = euclid::inv_mod(n + 1, mod);
        return (ll)((__int128)ret * inv % mod);
    }
};

// what: point update + range sum on a fixed-size array using a tree.
// time: build O(n), update/query O(log n); memory: O(n)
// constraint: 1-indexed [1, n]; a[0] unused.
// usage: seg_tree st; st.build(a); st.set(p, v); st.query(l, r);
struct seg_tree {
    int flag;
    vector<ll> t;
    void build(int n) {
        // goal: build tree from 1-indexed array.
        flag = 1;
        while (flag < n) flag <<= 1;
        t.assign(2 * flag, INF);
    }
    void set(int p, ll val) {
        // goal: set a[p] = val.
        for (t[p += flag - 1] = val; p > 1; p >>= 1)
            t[p >> 1] = min(t[p], t[p ^ 1]);
    }
    ll query(int l, int r) const { return query(l, r, 1, 1, flag); }
    ll query(int l, int r, int v, int nl, int nr) const {
        // result: sum on [l, r] within node range.
        if (r < nl || nr < l) return INF;
        if (l <= nl && nr <= r) return t[v];
        int mid = (nl + nr) >> 1;
        return min(query(l, r, v << 1, nl, mid), query(l, r, v << 1 | 1, mid + 1, nr));
    }
};

int n;
vector<int> a;
vector<vector<int>> ra;
catalan_mod ct;
seg_tree seg;

ll solve(int l, int r) {
    if (l >= r) return 1;

    int mn = seg.query(l, r);

    auto it1 = lower_bound(all(ra[mn]), l);
    auto it2 = upper_bound(all(ra[mn]), r);

    ll ret = ct.catalan(it2 - it1);
    if (it1 != it2)
        ret = ret * solve(l, *it1 - 1) % MOD;
    while (it1 != it2) {
        int nl = *it1 + 1, nr = -1;
        ++it1;
        if (it1 == ra[mn].end()) nr = r;
        else nr = min(r, *it1 - 1);

        ret = ret * solve(nl, nr) % MOD;
    }
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n; cin >> n;

    a.resize(n + 1);
    ra.resize(1010101);
    seg.build(n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ra[a[i]].push_back(i);
        seg.set(i, a[i]);
    }

    ct.init(n, MOD);

    cout << solve(1, n) << '\n';
}
