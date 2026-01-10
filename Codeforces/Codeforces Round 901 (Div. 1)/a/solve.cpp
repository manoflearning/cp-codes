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

constexpr int INF = 1e9 + 7;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n, m, k;
        cin >> n >> m >> k;

        vector<ll> a(n), b(m);
        for (auto &i : a) cin >> i;
        for (auto &i : b) cin >> i;

        for (int t = 0; t < 10 + (k & 1); t++) {
            if (!(t & 1)) {
                int mn_a = 0, mx_b = 0;
                for (int i = 0; i < n; i++) {
                    if (a[mn_a] > a[i]) mn_a = i;
                }
                for (int i = 0; i < m; i++) {
                    if (b[mx_b] < b[i]) mx_b = i;
                }

                if (a[mn_a] < b[mx_b])
                    swap(a[mn_a], b[mx_b]);
            } else {
                int mx_a = 0, mn_b = 0;
                for (int i = 0; i < n; i++) {
                    if (a[mx_a] < a[i]) mx_a = i;
                }
                for (int i = 0; i < m; i++) {
                    if (b[mn_b] > b[i]) mn_b = i;
                }

                if (a[mx_a] > b[mn_b])
                    swap(a[mx_a], b[mn_b]);
            }
        }

        ll ans = 0;
        for (auto &i : a) ans += i;

        cout << ans << '\n';
    }
}
