#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;
const int MOD = 998'244'353;
const int MAXN = 303030;

map<pii, pll> dp;
ll fac[] = { 1, 1, 2, 6, 24, 120, 720 };

pll f(int n, int x) {
    if (n <= 5) return { 1, n + 1 };

    auto& ret = dp[{ n, x }];
    ret = { 0, 1 };

    for (int num = 1; num <= 6; num++) {
        if (n + 1 < num) continue;
        if (x % 6 == num % 6) continue;

        int nxtn = n - ((n + 1) / 6 + ((n + 1) % 6 >= num));
        int nxtx = x - ((x + 1) / 6 + ((x + 1) % 6 >= num));
        pll prv = f(nxtn, nxtx);

        ret.fr = (ret.fr * prv.sc + prv.fr * ret.sc) % MOD;
        ret.sc = (ret.sc * prv.sc) % MOD;
    }
    ret.sc = ret.sc * 6 % MOD;

    return ret;
}

ll power(ll x, int y) {
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

    int n; cin >> n;

    for (int x = 1; x <= n; x++) {
        pll ans = f(n - 1, x - 1);
        // cout << ans.fr << ' ' << ans.sc << '\n';
        cout << ans.fr * power(ans.sc, MOD - 2) % MOD << '\n';
    }
}