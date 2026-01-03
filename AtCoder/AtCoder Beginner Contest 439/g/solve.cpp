#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
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

constexpr int N = 252525;
constexpr int M = N;
constexpr int L = 252525;

// what: multiply polynomials under a single NTT-friendly prime.
// time: O(n log n); memory: O(n)
// constraint: MOD is NTT prime, ROOT is primitive root; n is power of two.
// usage: auto c=ntt_mod<MOD,ROOT>::mul(a,b);
template <ll MOD_, ll ROOT_>
struct ntt_mod {
    static constexpr ll MOD = MOD_;
    static constexpr ll ROOT = ROOT_;

    static ll norm(ll x) {
        x %= MOD;
        if (x < 0) x += MOD;
        return x;
    }

    static ll mod_pow(ll b, ll e) {
        ll ans = 1;
        while (e) {
            if (e & 1) ans = ans * b % MOD;
            b = b * b % MOD;
            e >>= 1;
        }
        return ans;
    }

    static void ntt(vector<ll> &a) {
        // goal: inplace NTT of a.
        int n = sz(a), lg = 31 - __builtin_clz(n);
        static vector<ll> rt(2, 1);
        for (static int k = 2, s = 2; k < n; k <<= 1, s++) {
            rt.resize(n);
            ll z[] = {1, mod_pow(ROOT, MOD >> s)};
            for (int i = k; i < 2 * k; i++) rt[i] = rt[i / 2] * z[i & 1] % MOD;
        }
        vector<ll> rev(n);
        for (int i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << lg) / 2;
        for (int i = 0; i < n; i++)
            if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int k = 1; k < n; k <<= 1)
            for (int i = 0; i < n; i += 2 * k)
                for (int j = 0; j < k; j++) {
                    ll z = rt[j + k] * a[i + j + k] % MOD;
                    ll &ai = a[i + j];
                    a[i + j + k] = ai - z + (z > ai ? MOD : 0);
                    ai += (ai + z >= MOD ? z - MOD : z);
                }
    }

    static vector<ll> mul(const vector<ll> &a, const vector<ll> &b) {
        // result: convolution under MOD.
        if (a.empty() || b.empty()) return {};
        int s = sz(a) + sz(b) - 1;
        int n = 1;
        while (n < s) n <<= 1;
        int inv = mod_pow(n, MOD - 2);
        vector<ll> l(n, 0), r(n, 0), out(n);
        for (int i = 0; i < sz(a); i++) l[i] = norm(a[i]);
        for (int i = 0; i < sz(b); i++) r[i] = norm(b[i]);
        ntt(l);
        ntt(r);
        for (int i = 0; i < n; i++)
            out[-i & (n - 1)] = (ll)l[i] * r[i] % MOD * inv % MOD;
        ntt(out);
        return {out.begin(), out.begin() + s};
    }
};

// what: convolution wrapper specialized to the common 998244353 prime.
// time: O(n log n); memory: O(n)
// constraint: mod fixed to 998244353; n must be power of two.
// usage: auto c=ntt_conv::mul(a,b);
struct ntt_conv : ntt_mod<MOD, 3> {};

int n, m, l;
ll a[M], ans[M];
ll m_inv;

ll dp[N], pdp[N];

ll power(ll x, ll y) {
    if (!y) return 1;
    ll res = power(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

void naive() {
    vector<ll> aa(1), bb(n + 1);
    for (int i = 1; i <= m; i++) bb[a[i]] = m_inv;

    // base case
    aa[0] = 1;

    // inductive step
    for (int t = 1; t <= n; t++) {
        vector<ll> tmp(n + 1);
        
        aa = ntt_conv::mul(aa, bb);
        ll acc = 0;
        while (sz(aa) >= n + 2) {
            acc += aa.back();
            aa.pop_back();
        }
        aa.back() = (aa.back() + acc) % MOD;

        if (sz(aa) >= n + 1) {
            dp[t] = aa[n];
            aa.pop_back();
        }

        pdp[t] = (dp[t] + pdp[t - 1]) % MOD;
    }

    // get answer
    for (int t = 1; t <= n; t++) {
        if (dp[t] == 0) continue;

        const ll x = (1 - pdp[t] + MOD) % MOD;
        const ll y = (1 - pdp[t - 1] + MOD) % MOD;
        const ll y_inv = power(y, MOD - 2);

        ll x_pow = 1, y_pow = power(y, l - 1);
        for (int i = 1; i <= l; i++) {
            ll res = dp[t];
            res = res * x_pow % MOD;
            res = res * y_pow % MOD;

            ans[i] = (ans[i] + res) % MOD;

            x_pow = x_pow * x % MOD;
            y_pow = y_pow * y_inv % MOD;
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> l;
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
    }

    m_inv = power(m, MOD - 2);    

    naive();

    for (int i = 1; i <= l; i++) {
        cout << ans[i] << '\n';
    }
}
