#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

bool pos(const int lb, const int n, const int tgt, const vector<string> &a) {
    vector<vector<vector<short>>> dp(n + 1, vector<vector<short>>(n + 1, vector<short>(n + 1, - 1)));

    // base case
    dp[0][0][0] = 0;

    // inductive step
    for (int i = 0; i <= n; i++) {
        if (i > 0 && a[0][i - 1] == '#') continue;
        for (int j = 0; j <= n; j++) {
            if (j > 0 && a[1][j - 1] == '#') continue;
            for (int k = 0; k <= n; k++) {
                if (dp[i][j][k] == -1) continue;

                for (int p = max({i, j, k}); p <= n; p++) {
                    if (p == 0) continue;

                    bool xi{1}, xj{1}, xk{1};

                    xi &= (a[0][p - 1] == '.');
                    xi &= (!i || (p - i) * (p - i) + 0 >= lb);
                    xi &= (!j || (p - j) * (p - j) + 1 >= lb);
                    xi &= (!k || (p - k) * (p - k) + 4 >= lb);

                    xj &= (a[1][p - 1] == '.');
                    xj &= (!i || (p - i) * (p - i) + 1 >= lb);
                    xj &= (!j || (p - j) * (p - j) + 0 >= lb);
                    xj &= (!k || (p - k) * (p - k) + 1 >= lb);

                    xk &= (a[2][p - 1] == '.');
                    xk &= (!i || (p - i) * (p - i) + 4 >= lb);
                    xk &= (!j || (p - j) * (p - j) + 1 >= lb);
                    xk &= (!k || (p - k) * (p - k) + 0 >= lb);

                    if (xi) dp[p][j][k] = max<short>(dp[p][j][k], dp[i][j][k] + 1);
                    if (xj) dp[i][p][k] = max<short>(dp[i][p][k], dp[i][j][k] + 1);
                    if (xk) dp[i][j][p] = max<short>(dp[i][j][p], dp[i][j][k] + 1);
                    if (dp[p][j][k] == tgt) return 1;
                    if (dp[i][p][k] == tgt) return 1;
                    if (dp[i][j][p] == tgt) return 1;
                }
            }
        }
    }

    return 0;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, k;
    cin >> n >> k;

    vector<string> a(3);
    for (auto &i : a) cin >> i;

    int cnt_usable{};
    for (const auto &i : a) for (const auto &j : i) cnt_usable += j == '.';

    if (cnt_usable < k) {
        cout << -1 << '\n';
        return 0;
    }

    int l = 1, r = (n - 1) * (n - 1) + 2 * 2;
    while (l < r) {
        const int mid = (l + r + 1) >> 1;

        if (pos(mid, n, k, a)) l = mid;
        else r = mid - 1;
    }

    ld ans = sqrt(l);
    cout << fixed;
    cout.precision(10);
    cout << ans << '\n';

    return 0;
}
