#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

const int N = 202020;
const int MOD = 998'244'353;

int n;
ll a[N], psum[N];

ll sum(ll l, ll r) {
    return psum[r] - psum[l - 1];
}

// ll add_mod(ll x, ll y) { return (x + y) % MOD; }
// ll mul_mod(ll x, ll y) { return (x * y) % MOD; }

ll naive() {
    ll ret = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            ret = (ret + (a[i] % a[j]) % MOD * (a[i] % a[j]) % MOD) % MOD;
        }
    }
    return ret % MOD;
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        
        sort(a + 1, a + n + 1);

        for (int i = 1; i <= n; i++) {
            psum[i] = a[i] + psum[i - 1];
        }

        ll ans = 0;

        for (int i = 1; i <= n; i++) {
            ans = (ans + n * (a[i] % MOD) % MOD * (a[i] % MOD) % MOD) % MOD;
        }

        for (int j = 1; j <= n; j++) {
            int i = 1;

            while (i <= n) {
                const ll val = a[i] / a[j];

                int l = i, r = n;
                while (l < r) {
                    int mid = (l + r + 1) >> 1;
                    if (a[mid] / a[j] == val) l = mid;
                    else r = mid - 1;
                }

                int k = r;

                ans -= 2 * sum(i, k) % MOD * (a[j] % MOD) % MOD * (val % MOD) % MOD;

                ans += (k - i + 1) * (a[j] % MOD * val % MOD) % MOD * (a[j] % MOD * val % MOD) % MOD;
                ans %= MOD;
                ans = (ans + MOD) % MOD;

                i = k + 1;
            }
        }

        cout << ans << '\n';
        // cout << naive() << '\n';
    }
}
