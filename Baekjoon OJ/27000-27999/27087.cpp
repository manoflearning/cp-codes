#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int dp[121][121][121];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int a, b, c, p;
        cin >> a >> b >> c >> p;

        memset(dp, 0, sizeof(dp));

        dp[a][b][c] = 1;
        for (int i = a; i >= 0; i--) {
            for (int j = b; j >= 0; j--) {
                for (int k = c; k >= 0; k--) {
                    if (!dp[i][j][k]) continue;

                    if (i % p == 0 && j % p == 0 && k > 0) {
                        dp[i][j][k - 1] = 1;
                    }
                    if (i % p == 0 && k % p == 0 && j > 0) {
                        dp[i][j - 1][k] = 1;
                    }
                    if (j % p == 0 && k % p == 0 && i > 0) {
                        dp[i - 1][j][k] = 1;
                    }
                }
            }
        }

        cout << dp[0][0][0] << '\n';
    }
}
