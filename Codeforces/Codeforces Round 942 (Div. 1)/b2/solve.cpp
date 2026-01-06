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

// constexpr int M = 2020202;

ll dp[2020][2020];

ll gcd(ll x, ll y) {
    ll &ret = dp[x][y];
    if (ret != -1) return ret;
    if (!y) return ret = x;
    return ret = gcd(y, x % y);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    memset(dp, -1, sizeof(dp));

    int tc; cin >> tc;
    while (tc--) {
        ll n, m;
        cin >> n >> m;

        ll ans = 0;

        for (ll p = 1; (p + 1) * p <= n; p++) {
            ll lo = 0, hi = m;
            while (lo < hi) {
                const ll q = (lo + hi + 1) >> 1;
                if (n < (p + q) * p || m < (p + q) * q) hi = q - 1;
                else lo = q;
            }
            
            for (ll q = 1; q <= lo; q++) {
                if (gcd(p, q) > 1) continue;

                const ll a = (p + q) * p;
                const ll b = (p + q) * q;

                ans += min(n / a, m / b);
            }
        }

        cout << ans << '\n';
    }
}
