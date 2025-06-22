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
const int M = 1010101;

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}

ll dp[M], dp2[M];

ll f2(ll m) {
    ll &ret = dp2[m];
    if (ret != -1) return ret;
    if (m == 1) return ret = 1;

    ret = 1;
    for (int i = 2; i < m; i++) {
        if (gcd(i, m) == 1) continue;
        ret = (ret + 2 * f2(i)) % MOD;
    }
    ret = (ret + 2 * f2(1)) % MOD;
    
    return ret;
}

ll f(ll m) {
    ll &ret = dp[m];
    if (ret != -1) return ret;
    if (m == 1) return ret = 1;

    ret = 0;
    // case 1: don't use m
    ret = (ret + f(m - 1)) % MOD;
    // case 2: use m
    ret = (ret + f2(m)) % MOD;

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    memset(dp, -1, sizeof(dp));
    memset(dp2, -1, sizeof(dp2));

    int tc; cin >> tc;
    while (tc--) {
        int m; cin >> m;
        cout << f(m) << '\n';
    }
}
