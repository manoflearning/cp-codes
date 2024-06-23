#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

// const double EPS = 1e-8;

int r, c;
ll p;

double dp[1010][1010];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> r >> c >> p;

    for (int y = r - 1; y >= 0; y--) {
        for (int x = c - 1; x >= 0; x--) {
            if (y == r - 1 && x == c - 1) continue;

            else if (y == r - 1) dp[y][x] = dp[y][x + 1] + (double)p / 4;
            else if (x == c - 1) dp[y][x] = dp[y + 1][x] + (double)p / 4;
            else if (dp[y + 1][x] < dp[y][x + 1]) {
                double diff = dp[y][x + 1] - dp[y + 1][x];

                dp[y][x] += 0.5 * dp[y + 1][x];
                dp[y][x] += 0.5 * (dp[y + 1][x] + diff / 2) * diff / p;
                dp[y][x] += 0.5 * (p - diff) / p * dp[y][x + 1];
            }
            else if (dp[y + 1][x] > dp[y][x + 1]) {
                double diff = dp[y + 1][x] - dp[y][x + 1];

                dp[y][x] += 0.5 * dp[y][x + 1];
                dp[y][x] += 0.5 * (dp[y][x + 1] + diff / 2) * diff / p;
                dp[y][x] += 0.5 * dp[y + 1][x] * (p - diff) / p;
            }
            else if (dp[y + 1][x] == dp[y][x + 1]) {
                dp[y][x] += 0.5 * (dp[y + 1][x] + dp[y][x + 1]);
            }
        }
    }

    // for (int i = 0; i < r; i++) {
    //     for (int j = 0; j < c; j++) {
    //         cout << dp[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }

    cout << fixed;
    cout.precision(8);

    cout << dp[0][0];
}