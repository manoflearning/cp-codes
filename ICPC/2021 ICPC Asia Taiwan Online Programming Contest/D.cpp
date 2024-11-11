#include <bits/stdc++.h>
using namespace std;
#define ll long long

long double dp[333];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    int n; cin >> n;

    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] += 1 / (long double)(n - 1);
        for (int j = 2; j < i; j++) {
            dp[i] += 1 / (long double)(n - j + 1) * dp[j];
        }
    }

    cout << fixed;
    cout.precision(8);
    cout << dp[n];
}
