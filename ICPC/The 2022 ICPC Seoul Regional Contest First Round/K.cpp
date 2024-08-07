#include <bits/stdc++.h>
using namespace std;
#define ll long long

int dp[10101][2];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif
    
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    for (int i = 0; i < 10101; i++) 
        dp[i][0] = dp[i][1] = 1e9 + 7;

    int n, t, m, s, e;
    cin >> n >> t >> m >> s >> e;

    dp[s][0] = dp[s][1] = 0;
    for (int i = 0; i < t; i++) {
        int b = (i & 1);
        for (int j = 0; j < m; j++) {
            int u, v, w;
            cin >> u >> v >> w;

            dp[u][b] = min(dp[u][b], w + dp[v][!b]);
            dp[v][b] = min(dp[v][b], w + dp[u][!b]);
        }

        for (int i = 0; i < n; i++) {
            dp[i][b] = min(dp[i][b], dp[i][!b]);
        }
    }

    int ans = min(dp[e][0], dp[e][1]);
    cout << (ans == 1e9 + 7 ? -1 : ans);

    return 0;
}