#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MOD = 1e9 + 7;

ll power(ll x, ll y) {
    if (y == 0) return 1;
    if (y == 1) return x;
    ll res = power(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

// ll get_m(ll a, ll b, ll k) {
//     if (k == 1) return b;

//     ll ret = 0;
//     ret += (get_m(a, b, k - 1) + MOD - 1) * k;
//     return ( + (b - 1)) % MOD;
// }

ll binom(ll n, ll r) {
    if (r < 0 || n < r) return 0;
    r = min(r, n - r);
    ll ret = 1;
    for (ll i = 1; i <= r; i++) {
        ret = ret * (n % MOD + 1 - i) % MOD;
        ret = ret * power(i, MOD - 2) % MOD;
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
        ll a, b, k;
        cin >> a >> b >> k;

        ll n = k * (a - 1) + 1;
        
        if (b == 1) {
            cout << n << ' ' << 1 << '\n';
            continue;
        }

        // m = nCa * (b - 1) * k + 1
        ll m = (binom(n, a) * (b - 1) % MOD * k % MOD + 1) % MOD;
        cout << n % MOD << ' ' << m % MOD << '\n';
    }
}
