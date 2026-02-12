#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<ll> a(n);
        for (auto &i : a) cin >> i;

        vector<vector<int>> b(n);
        for (int i = 0; i < n; i++) {
            if (n <= a[i]) continue;
            b[a[i]].push_back(i);
        }

        ll ans = 0;
        for (ll p = 1; p < n; p++) { // time: O(n sqrt(n))
            if (p * p < n) {
                int j = 0;
                for (int i = 0; i < sz(b[p]); i++) {
                    while (j + 1 < sz(b[p]) && b[p][j] - b[p][i] < p * p) j++;
                    if (b[p][j] - b[p][i] == p * p) ans++;
                }
            }

            for (const int i : b[p]) {
                for (ll q = 1; q < p && p * q < n; q++) {
                    ans += 0 <= i - p * q && a[i - p * q] == q;
                    ans += i + p * q < n && a[i + p * q] == q;
                }
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
