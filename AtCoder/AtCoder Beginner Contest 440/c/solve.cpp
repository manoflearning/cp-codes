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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n, w;
        cin >> n >> w;

        vector<ll> psum(2 * w), c(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> c[i];

            psum[i % (2 * w)] += c[i];
        }

        for (int i = 1; i < 2 * w; i++)
            psum[i] += psum[i - 1];
        
        ll ans = INF;
        for (int x = 1; x <= 2 * w; x++) {
            int l = -x + 2 * w;
            int r = (w - x - 1) % (2 * w);
            if (r < 0) r += (2 * w);

            ll res = 0;
            if (l <= r) {
                res += psum[r] - (l ? psum[l - 1] : 0);
            } else {
                res += psum[2 * w - 1] - psum[l - 1];
                res += psum[r];
            }

            ans = min(ans, res);
        }

        cout << ans << '\n';
    }
}