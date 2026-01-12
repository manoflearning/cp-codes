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

int m;
map<ll, pair<vector<ll>, vector<ll>>> dp;

ll pow_mod(ll x, ll y) {
    if (!y) return 1;
    ll res = pow_mod(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

vector<ll> add(const vector<ll> &a, const vector<ll> &b) {
    vector<ll> ret(m + 1);
    for (int i = 1; i <= m; i++)
        ret[i] = (a[i] + b[i]) % MOD;
    return ret;
}
vector<ll> mul(const vector<ll> &a, const ll b) {
    vector<ll> ret(m + 1);
    for (int i = 1; i <= m; i++)
        ret[i] = (a[i] * b) % MOD;
    return ret;
}
vector<ll> concat(const vector<ll> &a, const vector<ll> &b) {
    vector<ll> ret(m + 1);

    ll acc_a = 0, acc_b = 0;
    for (int i = 1; i <= m; i++) {
        ret[i] -= acc_a * acc_b % MOD;
        acc_a = (acc_a + a[i]) % MOD;
        acc_b = (acc_b + b[i]) % MOD;
        ret[i] += acc_a * acc_b % MOD;
        
        ret[i] %= MOD;
        ret[i] = (ret[i] + MOD) % MOD;
    }

    return ret;
}

pair<vector<ll>, vector<ll>> f(ll n) {
    if (dp.count(n)) return dp[n];

    // base case

    pair<vector<ll>, vector<ll>> &ret = dp[n];
    vector<ll> &ret1 = ret.fr;
    vector<ll> &ret2 = ret.sc;

    if (n == 0) {
        ret1.assign(m + 1, 0);
        ret2.assign(m + 1, 0);
        return ret;
    }

    vector<ll> base(m + 1, 1);
    base[0] = 0;

    ret1 = base;
    ret2 = base;

    if (n == 1) return ret;

    // inductive step

    ll dep = 0;
    while ((1ll << dep) - 1 < n) dep++;
    
    assert(2 <= dep);
    const ll last = n - (1ll << (dep - 1)) + 1;
    const ll siz_l = (1ll << (dep - 2)) - 1 + min(last, 1ll << (dep - 2));
    const ll siz_r = n - (1 + siz_l);

    auto [res_l1, res_l2] = f(siz_l);
    auto [res_r1, res_r2] = f(siz_r);

    const ll m_pow_l = pow_mod(m, siz_l);
    const ll m_pow_r = pow_mod(m, siz_r);

    ret1 = add(
        mul(concat(base, res_l1), m_pow_r), 
        mul(concat(base, res_r1), m_pow_l)
    );
    ret1 = add(ret1, mul(base, m_pow_l * m_pow_r % MOD));
    ret2 = concat(concat(base, res_l1), res_r1);

    for (int i = 1; i <= m; i++) {
        ret2[i] = (ret2[i] + ret1[i]) % MOD;
        ret2[i] = (ret2[i] + res_l2[i] * m_pow_r % MOD * m) % MOD;
        ret2[i] = (ret2[i] + res_r2[i] * m_pow_l % MOD * m) % MOD;
    }

    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        dp.clear();

        ll n;
        cin >> n >> m;

        auto cnt = f(n).sc;
        
        ll acc = 0;
        for (int i = 1; i <= m; i++) {
            // cout << i << ' ' << cnt[i] << '\n';
            acc = (acc + cnt[i] * i) % MOD;
        }
        cout << acc << '\n';
    }
}
