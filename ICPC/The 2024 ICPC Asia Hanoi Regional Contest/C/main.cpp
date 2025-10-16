#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1e9 + 7;
const int N = 10101010;

ll fac[N];

ll power(ll x, ll y) {
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

    fac[0] = 1;
    for (int i = 1; i < N; i++)
        fac[i] = fac[i - 1] * i % MOD;

    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;

        ll ans = 1;
        ans = ans * power(fac[n], m) % MOD;
        ans = ans * power(fac[m], n) % MOD;

        cout << ans << '\n';
    }
}
