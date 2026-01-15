#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

constexpr int MOD = 1e9 + 7;

ll pow_mod(ll x, ll y) {
    if (!y) return 1;
    ll res = pow_mod(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

inline ll sum(ll l, ll r) {
    if (l > r) return 0;
    ll ret = 0;
    ret += r * (r + 1) / 2;
    ret -= l * (l - 1) / 2;
    return ret;
}

inline ll sum_prod(ll c, ll a, ll b) {
    if (a > b) return 0;
    if (c == 1) return b - a + 1;
    ll ret = 0;
    ret = pow_mod(c, b + 1) - pow_mod(c, a);
    ret = (ret + MOD) % MOD;
    ret = ret * pow_mod(c - 1, MOD - 2) % MOD;
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll n, m;
    cin >> n >> m;

    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    char op; cin >> op;

    const ll t = (3 * n * (n - 1) / 2 + n) % MOD;
    const ll t_inv = pow_mod(t, MOD - 2);

    if (op == 'S') {
        vector<ll> e(n + 1);

        for (ll i = 1; i <= n; i++) {
            ll res = 0;

            res += i % MOD;
            res += (i * (n - i + 1) - 1) * i % MOD;

            res += sum(1, i - 1) % MOD * (n - i + 1) % MOD;
            res += sum(i, i) * (n - i) % MOD;

            res += sum(i + 1, n) % MOD * i % MOD;
            res += sum(i, i) * (i - 1) % MOD;

            res += t - (1 + 3 * (i * (n - i + 1) - 1) % MOD);
            res %= MOD;
            res = (res + MOD) % MOD;

            res = res * t_inv % MOD;

            res = pow_mod(res, m);
            res = res * a[i] % MOD;

            e[i] = res;
        }

        ll acc_n = 0, acc_d = 0;
        for (int i = 1; i <= n; i++) {
            acc_n = (acc_n + e[i]) % MOD;
            acc_d = (acc_d + a[i]) % MOD;
        }
        ll ans = acc_n * pow_mod(acc_d, MOD - 2) % MOD;
        cout << ans;
    } else {
        vector<ll> ss(n + 2, 1), ps(n + 2, 0);
        for (int i = n; i >= 1; i--) {
            ss[i] = i * ss[i + 1] % MOD;
        }
        for (int i = 1; i <= n; i++) {
            ps[i] = (ps[i - 1] + ss[i]) % MOD;
        }

        ll e1 = 0;

        e1 += n * (n + 1) / 2 % MOD;
        // cout << e1 << '\n';
        for (ll r = 2; r <= n; r++) {
            e1 += ps[r - 1] * pow_mod(ss[r + 1], MOD - 2) % MOD;
            e1 %= MOD;
        }
        // cout << e1 << '\n';
        for (ll r = 2; r <= n; r++) {
            e1 += sum_prod(r, 2, r);
            e1 %= MOD;
        }
        // cout << e1 << '\n';
        for (ll l = 1; l + 1 <= n; l++) {
            e1 += sum_prod(l, 2, n - l + 1);
            e1 %= MOD;
        }
        // cout << e1 << '\n';
        e1 = e1 * t_inv % MOD;

        const ll em = pow_mod(e1, m);

        cout << em << '\n';
    }


}
