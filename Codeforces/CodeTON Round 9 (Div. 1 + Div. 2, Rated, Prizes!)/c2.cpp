#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        ll x, m;
        cin >> x >> m;

        ll ans = 0;
        for (ll y = 1; y <= min(m, x - 1); y++) {
            ll t = x ^ y;
            if (t % x != 0 && t % y == 0) {
                ans++;
            }
        }
        if (x <= m) ans += 1;

        ll mx_t = (m + x - 1) / x * x - 2 * x;
        // cout << mx_t << '\n';
        ans += max(0ll, (mx_t - x) / x);
        for (ll t = max(2 * x, mx_t + x); t <= m + 2 * x; t += x) {
            ll y = t ^ x;
            // cout << t << ' ' << y << '\n';
            if (y <= m) ans++;
        }

        cout << ans << '\n';
    }
}
