#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int M = 505050;
const int INF = 1e9 + 7;

vector<int> dp(M, INF);

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // base case
    dp[1] = 0;

    // inductive step
    for (int i = 3; i < M; i += 2) {
        dp[i] = min(dp[i], dp[i - 2] + 1);
        for (int j = 3; j * j <= i; j += 2) {
            if (i % j) continue;
            dp[i] = min(dp[i], dp[j] + dp[i / j]);
        }
    }

    int tc; cin >> tc;
    while (tc--) {
        int m; cin >> m;
        cout << (dp[m] == INF ? -1 : dp[m] + 1) << '\n';
    }
}
