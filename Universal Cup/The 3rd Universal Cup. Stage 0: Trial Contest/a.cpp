#include <bits/stdc++.h>
using namespace std;

const int N = 55;
const int SUM = N * 101010;
const int INF = 1e9 + 7;

int n;
int a[N], b[N];
vector<int> dp(SUM, INF);

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
    }

    dp[0] = 0;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        vector<int> tmp(SUM, INF);
        for (int j = 0; j < SUM; j++) {
            if (dp[j] == INF) continue;
            tmp[j + a[i]] = min(tmp[j + a[i]], dp[j]);
            tmp[j] = min(tmp[j], dp[j] + b[i]);
        }
        dp = tmp;
    }

    int ans = INF;
    for (int i = 0; i < SUM; i++) {
        ans = min(ans, max(i, dp[i]));
    }

    cout << ans;
}