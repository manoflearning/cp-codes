#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;

int n, s;
vector<int> a;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> s;
    a.resize(n);
    for (auto& i : a) cin >> i;

    sort(all(a));

    ll ans = 0;
    if (1 < a[0]) {
        ans += a[0] - 1;
        a[0] = 1;
    }
    if (a[n - 1] < s) {
        ans += s - a[n - 1];
        a[n - 1] = s;
    }

    ll d = (s - 1) / (n - 1);
    
    int cnt3 = (s - 1) % (n - 1);
    
    vector<vector<ll>> dp(n, vector<ll>(n, INF));
    dp[0][0] = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= min(i - 1, cnt3); j++) {
            int prv = 1 + d * (i - 1 - j) + (d + 1) * j;

            dp[i][j] = min(dp[i][j], abs(a[i] - (prv + d)) + dp[i - 1][j]);
            if (j < cnt3) {
                dp[i][j + 1] = min(dp[i][j + 1], abs(a[i] - (prv + d + 1)) + dp[i - 1][j]);
            }
        }
    }

    cout << ans + dp[n - 1][cnt3];
}