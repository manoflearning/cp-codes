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

constexpr ll INF = 1e18;

ll query(char dir, ll k) {
    cout << "? " << dir << ' ' << k << '\n';
    cout.flush();
    ll ret; cin >> ret;
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    
    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        ll add_mx = -INF, sub_mx = -INF;
        for (int i = 0; i < n; i++) {
            ll x, y;
            cin >> x >> y;
            add_mx = max(add_mx, x + y);
            sub_mx = max(sub_mx, x - y);
        }

        constexpr ll k = (ll)1e9;
        query('R', k);
        query('R', k);
        query('U', k);
        ll d1 = query('U', k);
        query('D', k);
        query('D', k);
        query('D', k);
        ll d2 = query('D', k);

        d1 -= 4 * k - add_mx;
        d2 -= 4 * k - sub_mx;

        cout << "! " << (d1 + d2) / 2 << ' ' << (d1 - d2) / 2 << '\n';
        cout.flush();
    }
}