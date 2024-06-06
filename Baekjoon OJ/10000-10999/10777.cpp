#include <bits/stdc++.h>
using namespace std;

const int N = 3030, M = 111;

int n, m, a[N], b[M], pb[M];
int dp[2][2][M][M];
int ans = 0;

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> m;
    for (int i = 1; i <= m; i++) cin >> b[i];
}

void update(int& x, int y) { x = max(x, y); }

void bottomup() {
    // base case
    dp[1][0][1][m] = 0;
    for (int i = 0; i <= m; i++) {
        int l = 1 + i, r = m - i - 1;
        if (l - 1 > r) break;
        dp[1][0][l][r] = pb[m] - pb[r];
    }
    for (int i = 0; i <= m; i++) {
        int l = 1 + i, r = m - i;
        if (l - 1 > r) break;
        dp[1][1][l][r] = pb[m] - pb[r] + a[1];
    }

    // inductive step
    for (int i = 2; i <= n; i++) {
        int j = i & 1;
        for (int l = 1; l <= m + 1; l++) {
            for (int r = l - 1; r <= m; r++) {
                {
                    int& res = dp[j][0][l][r];
                    res = max(res, dp[!j][0][l][r]);
                    for (int k = 0; 1 <= l - k && r + k + 1 <= m; k++) {
                        res = max(res, dp[!j][0][l - k][r + k + 1] + pb[r + k + 1] - pb[r]);
                    }
                    for (int k = 0; 1 <= l - k && r + k <= m; k++) {
                        res = max(res, dp[!j][1][l - k][r + k] + pb[r + k] - pb[r]);
                    }
                }

                {
                    int& res = dp[j][1][l][r];
                    for (int k = 0; 1 <= l - k && r + k <= m; k++) {
                        res = max(res, dp[!j][0][l - k][r + k] + pb[r + k] - pb[r] + a[i]);
                    }
                    for (int k = 0; 1 <= l - k - 1 && r + k <= m; k++) {
                        res = max(res, dp[!j][1][l - k - 1][r + k] + pb[r + k] - pb[r] + a[i]);
                    }
                }
            }
        }
    }

    // get answer
    for (int l = 1; l <= m + 1; l++) {
        for (int r = l - 1; r <= m; r++) {
            int sum0 = 0, sum1 = 0;

            int s = l, e = r;
            while (s <= e) {
                sum0 += b[e];
                if (s < e) sum1 += b[e];
                s++, e--;
            }

            ans = max(ans, dp[n & 1][0][l][r] + sum0);
            ans = max(ans, dp[n & 1][1][l][r] + sum1);
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    sort(b + 1, b + 1 + m);

    for (int i = 1; i <= m; i++) 
        pb[i] = pb[i - 1] + b[i];

    bottomup();

    cout << ans;
}