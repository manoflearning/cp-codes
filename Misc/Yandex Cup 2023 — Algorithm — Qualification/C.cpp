// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

ll naive(int n) {
    ll ret = 0;
    for (ll i = 1; i <= n; i++) {
        for (ll j = 1; j <= n; j++) {
            ret = (ret + (i & j)) % MOD;
        }
    }
    return ret;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        ll n; cin >> n;
        
        ll ans = 0;
        for (int d = 0; d <= 60; d++) {
            if (n < (1ll << d)) break;
            // ll x = n;
            // for (int i = 0; i <= d; i++) x -= (n & (1ll << i));
            ll x = 0;
            if (n & (1ll << d)) x = n / (1ll << (d + 1)) + 1;
            else x = n / (1ll << (d + 1));
            
            ll y = (1ll << d) - 1 + 1;
            if (n < (1ll << (d + 1))) {
                y = n - (1ll << d) + 1;
            }

            x %= MOD, y %= MOD;

            ll left = x % MOD * y % MOD;
            cout << (1ll << d) << ' ' << x << ' ' << y << '\n';
            ll res = (1ll << d) % MOD;
            res = res * left % MOD;
            res = res * left % MOD;
            ans = (ans + res) % MOD;
        }
        cout << n << ' ' << naive(n) << ' ';
        cout << ans << '\n';
    }
}