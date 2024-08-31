#include <bits/stdc++.h>
using namespace std;

int n, m;
int st, en;
double dp[505][10101];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin >> n >> m >> st >> en;

    double base = (double)1 / (n - 1);

    dp[st][0] = 1;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (1 < j && j < n) {
                dp[j][i] += (1.0 - 2 * base) * dp[j][i - 1];
                dp[j][i] += base * dp[j - 1][i - 1];
                dp[j][i] += base * dp[j + 1][i - 1];
            }
            else if (j == 1) {
                dp[j][i] += (1.0 - base) * dp[j][i - 1];
                dp[j][i] += base * dp[j + 1][i - 1];
            }
            else if (j == n) {
                dp[j][i] += (1.0 - base) * dp[j][i - 1];
                dp[j][i] += base * dp[j - 1][i - 1];
            }
        }
    }

    cout << fixed;
    cout.precision(8);

    cout << dp[en][m];
}