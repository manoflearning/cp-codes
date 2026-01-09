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

inline ll pow_mod(ll a, ll e) {
    ll r = 1 % MOD;
    a %= MOD;
    if (a < 0) a += MOD;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

struct comb_mod {
    int n;
    vector<ll> fac, ifac;
    void init(int n_) {
        n = n_;
        fac.assign(n + 1, 1);
        ifac.assign(n + 1, 1);
        for (int i = 1; i <= n; i++)
            fac[i] = fac[i - 1] * i % MOD;
        ifac[n] = pow_mod(fac[n], MOD - 2);
        for (int i = n; i >= 1; i--)
            ifac[i - 1] = ifac[i] * i % MOD;
    }
    ll ncr(int n_, int r) const {
        if (r < 0 || n_ < r || n_ > n) return 0;
        ll ret = fac[n_] * ifac[r] % MOD;
        ret = ret * ifac[n_ - r] % MOD;
        return ret;
    }
};

int n, k, kdiv2;
vector<vector<int>> t;
vector<int> siz, par;
comb_mod cb;

ll ans = 0;

void dfs(int v, int prv) {
    par[v] = prv;
    siz[v] = 1;
    for (int i : t[v]) {
        if (i == prv) continue;
        dfs(i, v);
        siz[v] += siz[i];
    }
}

void cal(int v) {
    ll cnt = 1;
    cnt *= cb.ncr(siz[v], k / 2) % MOD;
    cnt *= cb.ncr(n - siz[v], k / 2) % MOD;

    ans += cnt;
    ans %= MOD;

    // next
    for (int i : t[v]) {
        if (i != par[v]) cal(i);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k;
    t.assign(n + 1, vector<int>());
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        t[u].push_back(v);
        t[v].push_back(u);
    }

    if (k & 1) {
        cout << 1 << '\n';
        exit(0);
    }
    kdiv2 = k / 2;

    siz.assign(n + 1, 0);
    par.assign(n + 1, 0);

    cb.init(n);

    dfs(1, 0);

    cal(1);

    ans += cb.ncr(n, k);
    ans %= MOD;
    
    ans *= pow_mod(cb.ncr(n, k), MOD - 2);
    ans %= MOD;

    if (ans < 0) ans += MOD;
    cout << ans << '\n';
}
