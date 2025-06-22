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
        for (ll y = 1; y <= min(m, 3 * x); y++) {
            if (x == y) continue;
            ll t = x ^ y;
            if (x % t == 0 || y % t == 0) {
                ans++;
            }
        }

        cout << ans << '\n';
    }
}
