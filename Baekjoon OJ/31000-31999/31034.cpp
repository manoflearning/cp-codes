#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second

const ll INF = 1e18;

ll p2[44];
ll n_equals_k(ll n, ll k) {
    ll flag = 1, dep = 0;
    for (flag = 1; flag < n; flag <<= 1, dep++);
    assert(dep < 44);
    return n * (dep + 1) - p2[dep];
}

ll dp_naive[101][101];
ll f_naive(ll n, ll k) {
    ll &ret = dp_naive[n][k];
    if (ret != -1) return ret;
    if (k == 1) return ret = 0;

    ret = INF;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            if (n - i >= k - j)
                ret = min(ret, n + f_naive(i, j) + f_naive(n - i, k - j));
        }
    }
    return ret;
}

ll f(ll n, ll k) {
    if (k == 1) return 0;
    if (n == k) return n_equals_k(n, k);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    p2[0] = 1;
    for (int i = 1; i < 44; i++)
        p2[i] = 2 * p2[i - 1];

    memset(dp_naive, -1, sizeof(dp_naive));

    for (ll n = 1; n <= 30; n++) {
        for (ll k = 1; k <= n; k++) {
            cout << "n = " << n << ", " << "k = " << k << ", ans = " << f_naive(n, k) << '\n';
        }
        cout << '\n';
    }

    int tc; cin >> tc;
    while (tc--) {
        ll n, k;
        cin >> n >> k;
        
    }
}
