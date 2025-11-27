#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) (x).begin(), (x).end()

ll power(ll x, ll y, const int mod) {
    if (!y) return 1;
    ll res = power(x, y / 2, mod);
    return res * res % mod * (y & 1 ? x : 1) % mod;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    ll n, m, q;
    cin >> n >> m >> q;

    cout << power(m, n - q, 998244353) << '\n';
}