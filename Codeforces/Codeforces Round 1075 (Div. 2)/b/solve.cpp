#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ll INF = 1e18;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n; ll x;
        cin >> n >> x;

        ll acc = 0;
        ll mx = -INF;
        vector<ll> a(n), b(n), c(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i] >> b[i] >> c[i];
            acc += (b[i] - 1) * a[i];
            mx = max(mx, a[i] * b[i] - c[i]);
        }

        const ll rem = max(0ll, x - acc);

        if (rem > 0 && mx <= 0) cout << -1 << '\n';
        else {
            if (rem == 0) cout << 0 << '\n';
            else cout << (rem + mx - 1) / mx << '\n';
        }
    }
}
