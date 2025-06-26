#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MOD = 998'244'353;

ll power(ll x, ll y) {
    if (y == 0) return 1;
    if (y == 1) return x;
    ll res = power(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

ll binom(ll n, ll r) {
    ll x = 1, y = 1;
    for (int i = 1; i <= r; i++) {
        x = x * (n - i + 1) % MOD;
        y = y * i % MOD;
    }
    return x * power(y, MOD - 2) % MOD;
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
        ll n, h, w;
        cin >> n >> h >> w;

        if (min(h, w) < 2 * n) {
            cout << 0 << '\n';
            continue;
        }

        ll x = 1;
        x = x * power(binom(h - 2 * n + 1, 2) + (h - 2 * n + 1), 2) % MOD;
        x = x * power(binom(w - 2 * n + 1, 2) + (w - 2 * n + 1), 2) % MOD;

        ll y = 0;
        y = 2 * binom(h - 2 * n + 3, 4) % MOD * binom(w - 2 * n + 3, 4) % MOD;

        cout << (x - y + MOD) % MOD << '\n';
    }
}
