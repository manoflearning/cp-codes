#include <bits/stdc++.h>
using namespace std;

int gcd(int x, int y) {
    if (!y) return x;
    else return gcd(y, x % y);
}

int dp[1010];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    dp[1] = 3;
    for (int n = 2; n <= 1000; n++) {
        dp[n] += dp[n - 1];
        for (int x = 1; x < n; x++) 
            if (gcd(x, n) == 1) dp[n] += 2;
    }

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        cout << dp[n] << '\n';
    }
}