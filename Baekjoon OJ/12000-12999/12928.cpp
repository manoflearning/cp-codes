#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;

bool dp[MAXN][MAXN][MAXN * (MAXN - 1) / 2];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    int n, s;
    cin >> n >> s;

    if (n == 1 || n == 2) {
        cout << 0;
        exit(0);
    }

    // base case
    dp[3][1][1] = 1;
    dp[3][2][1] = 1;

    // inductive step
    for (int i = 3; i <= n - 1; i++) {
        for (int j = 1; j <= n - 1; j++) {
            for (int k = 1; k <= (i - 1) * (i - 2) / 2; k++) {
                if (dp[i][j][k]) {
                    dp[i + 1][j][k + 1] = 1;
                    dp[i + 1][j + 1][k + j] = 1;

                    dp[i + 1][1][k + 1] = 1;
                    dp[i + 1][1][k + j] = 1;
                }
            }
        }
    }

    // get answer
    for (int i = 1; i <= n - 1; i++) {
        if (dp[n][i][s]) {
            cout << 1;
            exit(0);
        }
    }
    cout << 0;
}