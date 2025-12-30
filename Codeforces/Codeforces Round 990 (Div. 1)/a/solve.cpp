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
        int n; cin >> n;

        vector<vector<ll>> a(2, vector<ll>(n));
        for (int i = 0; i < n; i++) cin >> a[0][i];
        for (int i = 0; i < n; i++) cin >> a[1][i];

        ll ans = 0;
        ll rem_mx = -INF;
        for (int i = 0; i < n; i++) {
            if (a[0][i] >= a[1][i]) {
                ans += a[0][i];
                rem_mx = max(rem_mx, a[1][i]);
            } else {
                ans += a[1][i];
                rem_mx = max(rem_mx, a[0][i]);
            }
        }

        cout << ans + rem_mx << '\n';
    }
}
