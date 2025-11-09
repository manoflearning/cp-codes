#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int INF = 1e9 + 7;
constexpr int N = 50505;
constexpr int M = 505;

int n, a[N];
int dp[N][M];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dp[i][j] = INF;
        }
    }

    for (int i = 1; i <= n; i++) {
        // base case
        dp[i][1] = 0;

        // inductive step
        for (int j = i - 1; j >= 1; j--) {
            if (a[j] >= a[i]) continue;
            int diff = a[i] - a[j];
            for (int k = 2; k < M; k++) {
                if (dp[j][k - 1] >= diff) continue;
                dp[i][k] = min(dp[i][k], diff);
            }
        }
    }

    int ans1 = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < M; j++) {
            if (dp[i][j] != INF) ans1 = max(ans1, j);
        }
    }

    cout << ans1 << '\n';
}