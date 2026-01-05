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
        int n; cin >> n;

        vector<vector<int>> a(2, vector<int>(n));
        for (int i = 0; i < n; i++) cin >> a[0][i];
        for (int i = 0; i < n; i++) cin >> a[1][i];

        int ans = 0;

        int mx = -1e9;
        for (int i = 0; i < n; i++) {
            ans += max(a[0][i], a[1][i]);
            mx = max(mx, min(a[0][i], a[1][i]));
        }

        cout << ans + mx << '\n';
    }
}