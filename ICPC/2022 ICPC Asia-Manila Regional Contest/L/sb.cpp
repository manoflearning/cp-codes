#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr ll INF = 1e18;

ll power(ll x, ll y, ll mod) {
    if (!y) return 1;

    ll res = power(x, y / 2, mod);
    return res * res % mod * (y & 1 ? x : 1) % mod;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        ll a, b, s, p, v;
        cin >> a >> b >> s >> p >> v;

        ll len = INF;
        vector<ll> div;
        for (ll i = 1; i * i <= p - 1; i++) {
            if ((p - 1) % i == 0) {
                if (power(a, i, p) == 1) {
                    len = i;
                    break;
                }

                if (power(a, (p - 1) / i, p) == 1) {
                    len = min(len, (p - 1) / i);
                }
            }
        }

        cout << len << '\n';

        // ll xi = s;
        // int ans = 0;

        // if (s != v)
        //     while (1) {
        //         xi = (a * xi + b) % p;

        //         ans++;

        //         if (xi == s) { ans = -1; break; }
        //         if (xi == v) break;
        //     }

        // if (ans != -1) {
        //     cout << ans << '\n';
        // } else {
        //     cout << "IMPOSSIBLE\n";
        // }
    }
}
