#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int MOD = 998'244'353;
constexpr int MAX = 202020;

array<ll, MAX> fac{}, ifac{};

ll modpow(ll b, ll e) {
    if (!e) return 1;
    ll res = modpow(b, e / 2);
    return res * res % MOD * (e & 1 ? b : 1) % MOD;
}

ll ncr(int n, int r) {
    if (n < 0 || n < r) return 0;
    return fac[n] * ifac[r] % MOD * ifac[n - r] % MOD;
}
ll nhr(int n, int r) { return ncr(n + r - 1, r); }

vector<vector<vector<ll>>> dp;
ll f_naive(int i, int l, int r, const int n, const int m) {
    ll &ret = dp[i][l][r];
    if (ret != -1) return ret;
    if (i == n) return ret = (r == m);
    
    ret = 0;
    for (int nl = l; nl <= r; nl++) {
        for (int nr = r; nr <= m; nr++) {
            ret = (ret + f_naive(i + 1, nl, nr, n, m)) % MOD;
        }
    }
    return ret;
}

ll naive(int n, int m) { // time: O(n^2 m^3)
    dp.assign(n + 1, vector<vector<ll>>(m + 1, vector<ll>(m + 1, -1)));
    ll ret = 0;
    for (int r = 1; r <= m; r++)
        ret = (ret + f_naive(1, 1, r, n, m)) % MOD;
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    fac[0] = 1;
    for (int i = 1; i < MAX; i++)
        fac[i] = i * fac[i - 1] % MOD;
    ifac[MAX - 1] = modpow(fac[MAX - 1], MOD - 2);
    for (int i = MAX - 1; i >= 1; i--)
        ifac[i - 1] = i * ifac[i] % MOD;

    ll n, m;
    cin >> n >> m;

    ll ans = 0;
    ans = (ans + ncr(n + m - 2, n - 1) * ncr(n + m - 2, m - 1)) % MOD;
    ans = (ans - ncr(n + m - 2, n - 2) * ncr(n + m - 2, n)) % MOD;
    ans = (ans + MOD) % MOD;
    cout << ans << '\n';
}
