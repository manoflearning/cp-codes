#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

int n, a[55];
int dp[55][1010101];

void init() {
    for (int i = 0; i < 55; i++) {
        for (int j = 0; j < 1010101; j++) {
            dp[i][j] = -INF;
        }
    }
}

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

void solve() {
    dp[0][505050] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 1010101; j++) {
            if (dp[i - 1][j] == -INF) continue;

            dp[i][j - a[i]] = max(dp[i - 1][j], dp[i][j - a[i]]);
            dp[i][j] = max(dp[i - 1][j], dp[i][j]);
            dp[i][j + a[i]] = max(dp[i - 1][j] + a[i], dp[i][j + a[i]]);
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    init();

    input();

    solve();

    cout << (dp[n][505050] == 0 ? -1 : dp[n][505050]);
}