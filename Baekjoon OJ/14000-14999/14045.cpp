#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int MAXN = 444;

int n;
vector<int> a(MAXN);
vector<vector<int>> dp(MAXN, vector<int>(MAXN, -1));

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // input
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    // base case
    for (int i = 1; i <= n; i++) {
        dp[i][i] = a[i];
    }

    // inductive step
    for (int len = 2; len <= n; len++) {
        for (int s = 1; s + len - 1 <= n; s++) {
            int e = s + len;

            for (int i = s + 1; i < e; i++) {
                if (dp[s][i - 1] == -1) continue;
                
                if (dp[s][i - 1] == dp[i][e - 1])
                    dp[s][e - 1] = dp[s][i - 1] + dp[i][e - 1];

                for (int j = i + 1; j < e; j++) {
                    if (dp[i][j - 1] == -1) continue;
                    if (dp[j][e - 1] == -1) continue;
                    
                    if (dp[s][i - 1] == dp[j][e - 1])
                        dp[s][e - 1] = dp[s][i - 1] + dp[i][j - 1] + dp[j][e - 1];
                }
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            ans = max(ans, dp[i][j]);
        }
    }

    cout << ans;
}
