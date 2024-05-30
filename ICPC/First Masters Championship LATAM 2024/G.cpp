#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

int n, m;
int a[55][55];
int dp[55][55];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    // base case
    dp[n - 1][0] = a[n - 1][0];
    for (int j = 1; j < m; j++) {
        dp[n - 1][j] = a[n - 1][j] | dp[n - 1][j - 1];
    }

    // inductive step
    for (int i = n - 2; i >= 0; i--) {
        dp[i][0] = max(a[i][0], dp[i + 1][0]);
        for (int j = 1; j < m; j++) {
            if (a[i][j]) {
                dp[i][j] = dp[i + 1][j - 1] + 1;
            }
            dp[i][j] = max({ dp[i][j], dp[i+1][j], dp[i][j - 1] });
        }
    }

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < m; j++) {
    //         cout << dp[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }

    cout << dp[0][m - 1];
}