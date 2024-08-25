#include <bits/stdc++.h>
using namespace std;

const int MOD = 9901;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    // build graph
    vector<vector<int>> adj(1 << m);
    for (int b1 = 0; b1 < (1 << m); b1++) {
        for (int b2 = b1; b2 < (1 << m); b2++) {
            if ((b1 & b2) != b1) continue;
            bool is_valid = 1;
            int rem = b2 - b1, len = 0;
            for (int i = 0; i <= m; i++) {
                if (rem & (1 << i)) len++;
                else {
                    if (len & 1) is_valid = 0;
                    len = 0;
                }
            }
            if (is_valid) adj[b1].push_back(b2);
        }
    }

    // base case
    vector<vector<int>> dp(n, vector<int>(1 << m, 0));

    for (auto& now : adj[0]) {
        dp[0][now] = 1;
    }

    // inductive step
    for (int y = 1; y < n; y++) {
        for (int prv = 0; prv < (1 << m); prv++) {
            if (!dp[y - 1][prv]) continue;
            int now_base = (1 << m) - 1 - prv;
            for (auto& now : adj[now_base]) {
                dp[y][now] = (dp[y][now] + dp[y - 1][prv]) % MOD;
            }
        }
    }

    cout << dp[n - 1][(1 << m) - 1];
}