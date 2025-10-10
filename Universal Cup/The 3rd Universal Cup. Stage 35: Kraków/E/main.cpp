#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MOD = 998'244'353;

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}

ll power(const ll x, const ll y) {
    if (y == 0) return 1;
    if (y == 1) return x;
    ll res = power(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
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
        ll g = gcd(a, b);

        if (__builtin_popcountll(n / g) != 1) {
            cout << 2 << '\n';
            continue;
        }

        int m = 1;
        while (a != b) {
            m++;
            if (a > b) swap(a, b);
            b -= a, a += a;
        }

        ll p = power(2, m) - 1;
        ll q = power(2, m - 1);

        cout << p * power(q, MOD - 2) % MOD << '\n';
    }
}
