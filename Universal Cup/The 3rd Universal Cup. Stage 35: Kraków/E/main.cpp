#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

__int128_t power(const __int128_t x, const __int128_t y, const ll mod) {
    if (y == 0) return 1;
    if (y == 1) return x;
    __int128_t res = power(x, y / 2, mod);
    return res * res % mod * (y & 1 ? x : 1) % mod;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc; cin >> tc;
    while (tc--) {
        ll a, b;
        cin >> a >> b;

        ll n = a + b;

        ll m = -1;
        for (ll i = 1; i <= 100; i++) {
            if (a * power(2, i - 1, n / 2) % (n / 2) == 0) {
                m = i;
                break;
            }
        }

        const int MOD = 998'244'353;

        if (m != -1 && n % 2 == 0) {
            ll p = (power(2, m, MOD) + MOD - 1) % MOD;
            ll q = power(2, m - 1, MOD);

            cout << p * (ll)power(q, MOD - 2, MOD) % MOD << '\n';
        } else {
            cout << 2 << '\n';
        }

        // cout << m << '\n';
    }
}
