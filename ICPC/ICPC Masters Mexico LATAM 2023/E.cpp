#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1e9 + 7;

int n, d, k, s;

ll power(ll x, ll y) {
    if (y == 0) return 1;
    if (y == 1) return x;
    ll res = power(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

ll solve(ll p, ll x) {
    if (x == 0) return 1;
    if (x == 1) return 1 + p;

    if (x & 1) {
        ll res = solve(p, x / 2);
        return (res + res * power(p, x / 2 + 1)) % MOD;
    } else {
        ll res = solve(p, (x - 1) / 2);
        return ((res + res * power(p, (x - 1) / 2 + 1)) % MOD + power(p, x)) % MOD;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> d >> k >> s;

    ll p = min(n, 2 * d + 1);
    cout << solve(p, k - 1);
}
