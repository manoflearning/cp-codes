#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cout << fixed;
    cout.precision(10);

    int tc; cin >> tc;
    while (tc--) {
        int n, k, d;
        cin >> n >> k >> d;

        const int b = n % k, a = k - b;

        const int r = n / k;

        const ld A = (ld)(r * d + 1) / 2;
        const ld B = (ld)((r + 1) * d + 1) / 2;

        vector<vector<ld>> dp(a + 1, vector<ld>(b + 1));
        
        // base case
        dp[a][b] = 0;
        
        // inductive step
        for (int i = a; i >= 0; i--) {
            for (int j = b; j >= 0; j--) {
                // if (i == a && j == b) continue;

                const int deg = max(1, (i != a) + (j != b));
                const ld E = dp[i][j] / deg;

                if (j > 0) {
                    if (i > 0) dp[i][j - 1] += E + (0.5 * A + 1.5 * B - 1);
                    else dp[i][j - 1] += E + B;
                }
                if (i > 0) {
                    dp[i - 1][j] += E + A;
                }
            }
        }

        // cout << "A = " << A << ", B = " << B << '\n'; 
        // for (int i = 0; i <= a; i++) {
        //     for (int j = 0; j <= b; j++) {
        //         cout << i << ' ' << j << ' ' << dp[i][j] << '\n';
        //     }
        // }

        const int deg = max(1, (0 != a) + (0 != b));
        cout << dp[0][0] / deg << '\n';
    }
}
