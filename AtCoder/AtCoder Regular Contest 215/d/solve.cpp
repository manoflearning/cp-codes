#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int MOD = 1e9 + 7;
constexpr int N = 20202020;

array<ll, 2 * N> fac{}, ifac{};

ll modpow(ll x, ll y) {
    if (!y) return 1;
    const ll res = modpow(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

ll ncr(int n, int r) {
    if (n < 0 || n < r) return 0;
    return fac[n] * ifac[r] % MOD * ifac[n - r] % MOD;
}
ll nhr(int n, int r) { return ncr(n + r - 1, r); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    fac[0] = 1;
    for (int i = 1; i < 2 * N; i++) fac[i] = i * fac[i - 1] % MOD;
    ifac[2 * N - 1] = modpow(fac[2 * N - 1], MOD - 2);
    for (int i = 2 * N - 1; i >= 1; i--)
        ifac[i - 1] = i * ifac[i] % MOD;

    int n, m;
    cin >> n >> m;

    ll ans = 0;
    ans = (ans + nhr(n + 1, 2 * m)) % MOD;

    // ans = (ans - nhr((n - 1) / 2, m + 1) * nhr(n + 1, m - 1) % MOD) % MOD;
    // ans = (ans - nhr((n - 0) / 2, m + 1) * nhr(n + 1, m - 1) % MOD) % MOD;
    for (int i = 1; i <= m; i++) {
        ans = (ans - nhr((n - 1) / 2, m + i) * nhr(n + 1 - (n - 1) / 2, m - i) % MOD) % MOD;
        ans = (ans - nhr((n - 0) / 2, m + i) * nhr(n + 1 - (n - 0) / 2, m - i) % MOD) % MOD;
        ans = (ans + MOD) % MOD;
    }

    ans = (ans + MOD) % MOD;

    cout << ans << '\n';

    return 0;
}
