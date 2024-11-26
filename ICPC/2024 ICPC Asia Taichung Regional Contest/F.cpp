#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 998244353;

namespace miller_rabin {
ll mul(ll x, ll y, ll mod) { return (__int128_t)x * y % mod; }
ll ipow(ll x, ll y, ll p) {
  ll ret = 1, piv = x % p;
  while (y) {
    if (y & 1) ret = mul(ret, piv, p);
    piv = mul(piv, piv, p);
    y >>= 1;
  }
  return ret;
}
bool miller_rabin(ll x, ll a) {
  if (x % a == 0) return 0;
  ll d = x - 1;
  while (1) {
    ll tmp = ipow(a, d, x);
    if (d & 1) return (tmp != 1 && tmp != x - 1);
    else if (tmp == x - 1) return 0;
    d >>= 1;
  }
}
bool isprime(ll x) {
  for (auto &i : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (x == i) return 1;
    if (x > 40 && miller_rabin(x, i)) return 0;
  }
  if (x <= 40) return 0;
  return 1;
}
}; // namespace miller_rabin

map<pair<ll, ll>, ll> dp;

ll f(ll l, ll r) {
    if (dp.count({l, r})) return dp[{l, r}];
    ll &ret = dp[{l, r}];
    // base case
    bool is_done = 1;
    for (ll x = (l + 1) / 2; x <= r / 2; x++) {
        if (miller_rabin::isprime(x)) { is_done = 0; break; }
    }
    if (is_done) return ret = 1;

    cout << l / 2.0 << ' ' << r / 2.0 << '\n';

    // inductive step
    for (ll i = (l + r) / 2; i >= l; i--) {
        if (miller_rabin::isprime(i)) {
            ret = (ret + f(i, r)) % MOD;
        }
    }

    for (ll i = (l + r + 1) / 2; i <= r; i++) {
        if (miller_rabin::isprime(i)) {
            ret = (ret + f(l, i)) % MOD;
        }
    }

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        ll l, r;
        cin >> l >> r;

        cout << f(2 * l, 2 * r) << '\n';
    }
}
