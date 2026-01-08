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
        int n, m, k;
        cin >> n >> m >> k;

        if (n < 2 * k) { // wlog
            k = n - k + 1;
        }

        const int lcnt = k - 1;
        const int rcnt = n - k;

        // const int ub_days = max(2 * rcnt - 1, n + lcnt - 2);

        int ans = 1;
        for (int i = 1; i <= rcnt; i++) {
            int j = min(lcnt, i);

            int res = 0;
            if (m <= 2 * i - 1) {
                int t = (m + 1) / 2;
                res = t + 1;
            } else if (2 * i - 1 >= 1 && m <= (2 * i - 1) + j - 1) {
                int t = 2 * i - 1;
                res = 1 + i + min(j - 1, (m - t));
            } else {
                res = j + 1 + i;
            }

            ans = max(ans, res);
        }

        cout << ans << '\n';
    }
}
