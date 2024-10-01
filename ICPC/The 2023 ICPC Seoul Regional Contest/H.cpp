#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define all(x) (x).begin(), (x).end()

const int MAXN = 10101;

int n;
pii a[MAXN];
int dp[MAXN][MAXN];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].fr;
    for (int i = 1; i <= n; i++) cin >> a[i].sc;

    sort(a + 1, a + n + 1);

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            if (a[i].fr >= a[i].sc) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j] + a[i].fr);
            } else {
                dp[i][j] = max(dp[i][j], dp[i - 1][j] + a[i].sc);
            }

            if (a[j].sc < a[i].sc) {
                dp[i][i] = max(dp[i][i], dp[i - 1][j] + a[i].fr + a[i].sc);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i <= n; i++)
        ans = max(ans, dp[n][i]);
    cout << ans;
}
