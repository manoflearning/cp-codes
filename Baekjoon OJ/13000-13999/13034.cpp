#include <bits/stdc++.h>
using namespace std;

int n, dp[1010];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin >> n;

    dp[0] = dp[1] = 0;
    for (int i = 2; i < 1010; i++) {
        vector<int> vis(1010);
        for (int j = 0; ; j++) {
            int k = i - 2 - j;
            if (j > k) break;
            vis[dp[j] ^ dp[k]] = 1;
        }
        for (int j = 0; j < 1010; j++) {
            if (!vis[j]) { dp[i] = j; break; }
        }
    }

    cout << (dp[n] > 0 ? 1 : 2);
}
