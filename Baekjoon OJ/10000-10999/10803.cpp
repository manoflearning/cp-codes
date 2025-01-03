#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010, MAXM = 101;

int n, m;
int dp[MAXN][MAXM];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXM; j++) {
            dp[i][j] = 1e9 + 7;
        }
    }

    for (int i = 1; i < MAXN; i++) dp[i][1] = i;
    for (int i = 1; i < MAXM; i++) dp[1][i] = i;
    
    for (int i = 2; i < MAXN; i++) {
        for (int j = 2; j < MAXM; j++) {
            if (i % j == 0) dp[i][j] = min(dp[i][j], i / j);
            if (j % i == 0) dp[i][j] = min(dp[i][j], j / i);
            for (int k = 1; k <= i; k++)
                dp[i][j] = min(dp[i][j], dp[k][j] + dp[i - k][j]);
            for (int k = 1; k <= j; k++)
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[i][j - k]);
        }
    }

    cin >> n >> m;
    int cnt = 0;
    if (n >= 10 * m) {
        cnt = (n - 9 * m) / m;
        n -= cnt * m;
    }
    cout << cnt + dp[n][m];
}