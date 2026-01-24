#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int INF = 1e9 + 7;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    vector<string> a(n);
    for (auto &i : a) cin >> i;

    vector<vector<int>> dp(n + 1, vector<int>(n + 1));
    {
        int cntb = 0, cntw = 0;
        for (int i = 0; i < n; i++) {
            cntb += a[0][i] == '#';
            dp[0][i + 1] += cntb;
        }

        for (int i = n - 1; i >= 0; i--) {
            cntw += a[0][i] == '.';
            dp[0][i] += cntw;
        }
    }

    for (int i = 1; i < n; i++) {
        int cntb = 0, cntw = 0;
        for (int j = 0; j < n; j++) cntb += a[i][j] == '#';

        int prv = INF;
        for (int j = n; j >= 0; j--) {
            prv = min(prv, dp[i - 1][j]);

            dp[i][j] = cntb + cntw + prv;

            if (j > 0) {
                cntb -= a[i][j - 1] == '#';
                cntw += a[i][j - 1] == '.';
            }
        }
    }

    int ans = INF;
    for (int i = 0; i <= n; i++) ans = min(ans, dp[n - 1][i]);

    cout << ans << '\n';

    return 0;
}
