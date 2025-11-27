#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(x) (x).begin(), (x).end()

constexpr int N = 202020;

int n, a[N];
int dp[N];

int main() {
    // #ifndef ONLINE_JUDGE
    // freopen("../input.txt", "r", stdin);
    // freopen("../output.txt", "w", stdout);
    // #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    int mx = 0;
    for (int i = 1; i <= n; i++) {
        mx = max(mx, i - a[i]);
        dp[i] = i - mx;
    }

    int mn = n + 1;
    for (int i = n; i >= 1; i--) {
        mn = min(mn, i + a[i]);
        dp[i] = min(dp[i], mn - i);
    }

    // for (int i = 1; i <= n; i++) {
    //     cout << a[i] << ' ';
    // }
    // cout << '\n';
    // for (int i = 1; i <= n; i++) {
    //     cout << dp[i] << ' ';
    // }
    // cout << '\n';

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans;
}