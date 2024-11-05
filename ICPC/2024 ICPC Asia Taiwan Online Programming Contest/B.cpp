#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAXN = 303030;
const ll INF = 1e18;

int n;
ll a[MAXN], psum[MAXN];
ll dp[2][MAXN];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        psum[i] = a[i] + psum[i - 1];
    }

    ll prv_mx = 0;

    for (int i = 1; i <= n; i++) {
        dp[0][i] = dp[1][i] = -INF;
        {
            dp[0][i] = dp[0][i - 1] + max(a[i], -a[i]);
        }
        {
            dp[1][i] = max(dp[1][i], dp[1][i - 1] + max(a[i], -a[i]));
            dp[1][i] = max(dp[1][i], 2 * psum[i] + prv_mx);
        }
        {
            prv_mx = max(prv_mx, dp[0][i] - 2 * psum[i]);
        }
    }

    cout << dp[1][n];
}
