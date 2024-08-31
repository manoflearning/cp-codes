#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;

double dp[MAXN];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = i - 1; j >= max(0, i - m); j--) {
            dp[i] += (double)1 / (n - j) * dp[j];
        }
    }

    cout << fixed;
    cout.precision(8);

    cout << dp[n];
}