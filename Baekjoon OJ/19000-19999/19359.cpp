#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1e9 + 7;
const int MAXN = 2020;

ll power(ll x, ll y) {
    if (y == 0) return 1;
    if (y == 1) return x;
    ll res = power(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    while (1) {
        int n; cin >> n;
        if (cin.eof()) break;
        
        vector<ll> w(n + 2);
        for (int i = 1; i <= n; i++) cin >> w[i];

        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            ll res = w[i];
            res = res * (power(i, 3) - power(i - 1, 3)) % MOD;
            res = res * power(n, n - 3) % MOD;
            // res = res * (n - 3 + 1) % MOD;

            ans = (ans + res) % MOD;
        }

        cout << (ans + MOD) % MOD << '\n';
    }
}