#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

ll dp[10101];

ll power(ll x, ll y, ll mod) {
    if (y == 0) return 1;
    if (y == 1) return x % mod;
    ll res = power(x, y / 2, mod);
    return res * res % mod * (y & 1 ? x : 1) % mod;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int p, n;
    cin >> p >> n;

    for (int i = 0; i < p; i++) {
        dp[power(i, n, p)]++;
    }

    ll ans = 0;
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < p; j++) {
            ans += dp[(i + j) % p] * dp[i] * dp[j];
        }
    }

    cout << ans;
}
