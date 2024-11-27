#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MOD = 1e9 + 7;
const int MAXN = 1010101;

int n, kr, kg, kb;
ll dp[MAXN][3], pdp[MAXN][3];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> kr >> kg >> kb;

    // base case
    dp[1][0] = pdp[1][0] = 1;
    dp[1][1] = pdp[1][1] = 1;
    dp[1][2] = pdp[1][2] = 1;
    
    // inducitve step
    for (int i = 2; i <= n; i++) {
        int prvk = max(0, i - kr - 1);
        int prvg = max(0, i - kg - 1);
        int prvb = max(0, i - kb - 1);

        if (i <= kr) dp[i][0]++;
        if (i <= kg) dp[i][1]++;
        if (i <= kb) dp[i][2]++;

        dp[i][0] = (dp[i][0] + (pdp[i - 1][1] - pdp[prvk][1])) % MOD;
        dp[i][0] = (dp[i][0] + (pdp[i - 1][2] - pdp[prvk][2])) % MOD;
        dp[i][1] = (dp[i][1] + (pdp[i - 1][0] - pdp[prvg][0])) % MOD;
        dp[i][1] = (dp[i][1] + (pdp[i - 1][2] - pdp[prvg][2])) % MOD;
        dp[i][2] = (dp[i][2] + (pdp[i - 1][0] - pdp[prvb][0])) % MOD;
        dp[i][2] = (dp[i][2] + (pdp[i - 1][1] - pdp[prvb][1])) % MOD;

        pdp[i][0] = (dp[i][0] + pdp[i - 1][0]) % MOD;
        pdp[i][1] = (dp[i][1] + pdp[i - 1][1]) % MOD;
        pdp[i][2] = (dp[i][2] + pdp[i - 1][2]) % MOD;
    }

    ll ans = dp[n][0] + dp[n][1] + dp[n][2];
    ans %= MOD;
    ans = (ans + MOD) % MOD;
    cout << ans;
}
