#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()

ll f(int n, const vector<ll> &a) {
    ll ret = LLONG_MAX;

    ll mn = LLONG_MAX;
    mn = min(mn, a[1]);
    for (int i = 2; i <= n; i++) {
        if (a[i] == 0) {
            if (mn < 0) {
                ret = min(ret, 0ll);
            }
        } else if (a[i] > 0) {
            if (mn < a[i]) {
                ret = min(ret, a[i] * mn);
            }
        }
        mn = min(mn, a[i]);
    }

    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        ll n, l, r, x, y, z;
        cin >> n >> l >> r >> x >> y >> z;

        vector<ll> b(n + 1), a(n + 1);
        cin >> b[1] >> b[2];
        for (int i = 3; i <= n; i++) {
            b[i] = ((__int128_t)b[i - 2] * x + (__int128_t)b[i - 1] * y + z) & ((1ll << 32) - 1);
        }

        for (int i = 1; i <= n; i++) {
            a[i] = b[i] % (r - l + 1) + l;
        }

        ll ans = LLONG_MAX;

        ans = min(ans, f(n, a));
        for (int i = 1; i <= n; i++) {
            a[i] *= -1;
        }
        for (int i = 1; i <= n / 2; i++) {
            swap(a[i], a[n - i + 1]);
        }
        ans = min(ans, f(n, a));
        
        if (ans == LLONG_MAX) {
            cout << "IMPOSSIBLE\n";
        } else {
            cout << ans << '\n';
        }
    }
}