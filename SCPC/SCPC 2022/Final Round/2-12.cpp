// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const int MAXN = 3030;

int n;
ll a[MAXN];
// ll psum[MAXN];
ll dp[MAXN][MAXN];

void init() {}

void input() {
    cin >> n;
    a[0] = 0;
    for (int i = 1; i <= n; i++) cin >> a[i];
    a[n + 1] = 0;
}

// void buildPsum() {
//     for (int i = 1; i < n; i++)
//         psum[i] = a[i] + psum[i - 1];
// }

// ll sum(int l, int r) {
//     return psum[r] - psum[l - 1];
// }

void f() { // dp[l][r] = [l, r] 범위에서 최적해
    // base case
    for (int i = 1; i <= n; i++) {
        dp[i][i] = a[i];
    }
    
    // inductive step
    for (int len = 2; len <= n; len++) {
        for (int l = 1; ; l++) {
            int r = l + len - 1;
            if (n < r) break;

            dp[l][r] = 0;
            for (int i = l; i <= r; i++) {
                dp[l][r] = max(dp[l][r], a[i] + min(dp[l][i - 1], dp[i + 1][r]));
            }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        init();

        input();

        // buildPsum();

        f();
        
        cout << dp[1][n] << '\n';

        cout << flush;
    }
}
