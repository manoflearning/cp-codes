#pragma GCC optimize ("O3")
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
        int n, m, k;
        cin >> n >> m >> k;

        vector<string> a(n);
        for (auto &i : a) cin >> i;

        vector<vector<int>> psum(n + 1, vector<int>(m));
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < m; y++) {
                psum[x + 1][y] += (a[x][y] == 'x');
                psum[x + 1][y] += psum[x][y];
            }
        }

        int ans = 0;

        vector<vector<bool>> dp(n, vector<bool>(m));
        // base case
        dp[0][0] = 1;

        // inductive step
        for (int x = 0; x + k <= n; x++) {
            for (int y = 0; y + 1 < m; y++) {
                if (!dp[x][y]) continue;
                if (psum[x + k][y + 1] - psum[x][y + 1] == 0) {
                    dp[x][y + 1] = 1;
                }
            }
            for (int y = m - 1; y >= 1; y--) {
                if (!dp[x][y]) continue;
                if (psum[x + k][y - 1] - psum[x][y - 1] == 0) {
                    dp[x][y - 1] = 1;
                }
            }

            if (x + k + 1 <= n)
            for (int y = 0; y < m; y++) {
                if (!dp[x][y]) continue;
                if (psum[x + k + 1][y] - psum[x + 1][y] == 0) {
                    dp[x + 1][y] = 1;
                    ans = max(ans, x + 1);
                }
            }
        }

        cout << ans + k << '\n';
    }
}