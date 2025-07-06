#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const ll INF = 1e18;
const int M = 2;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; ll k;
        cin >> n >> k;

        vector<ll> a(n);
        for (auto &i : a) {
            cin >> i;
            i %= k;
        }

        vector<array<ll, M>> b(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < M; j++) {
                b[i][j] = a[i] + k * j;
            }
        }

        vector<array<ll, M>> dp(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < M; j++) dp[i][j] = INF;

        // base case
        for (int i = 0; i < M; i++) {
            dp[0][i] = b[0][i];
        }

        // inductive step
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < M; j++) {
                for (int k = 0; k < M; k++) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][k] + max(0ll, b[i][j] - b[i - 1][k]));
                    dp[i][j] = min(dp[i][j], dp[i - 1][k] + b[i][j]);
                }
            }
        }

        ll ans = INF;
        for (int i = 0; i < M; i++) {
            ans = min(ans, dp[n - 1][i]);
        }
        cout << ans << '\n';
    }
}
