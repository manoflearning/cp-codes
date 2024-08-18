#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        ll n; cin >> n;

        ll l = 0, r = 1e9;
        while (l < r) {
            ll mid = (l + r + 1) >> 1;
            if (mid * mid + mid > n) r = mid - 1;
            else l = mid;
        }

        ll p = l;

        ll ans = p * p;

        ll s = 0, e = p;
        while (s < e) {
            ll mid = (s + e + 1) >> 1;
            if ((p + 1) * (p + 1) + mid > n) e = mid - 1;
            else s = mid;
        }

        ans += 2 * s;
        cout << ans << '\n';
    }
}
