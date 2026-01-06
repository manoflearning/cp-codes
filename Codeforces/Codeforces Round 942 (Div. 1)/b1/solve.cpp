#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        ll n, m;
        cin >> n >> m;

        ll ans = 0;
        ans += n;
        for (ll b = 2; b <= m; b++) {
            ll res = n;
            res /= b;
            res++;
            res /= b;
            ans += res;
        }

        cout << ans << '\n';
    }
}
