// naive
// dp[i][j] = max(a[k] + min(dp[i][k - 1], dp[k + 1][j])) (i <= k <= j)

// dp[i][j] <= dp[i][j + 1], dp[i][j] <= dp[i - 1][j]

// k <= K[i][j]인 경우 dp[i][k - 1] < dp[k + 1][j]이고
// k > K[i][j]인 경우 dp[i][k - 1] >= dp[k + 1][j]인 K[i][j]가 존재한다.

// K[i - 1][j] <= K[i][j] <= K[i][j + 1]
// k > K[i][j]에 대해 dp[i - 1][k - 1] >= dp[i][k - 1] >= dp[k + 1][j]이므로
// K[i - 1][j] <= K[i][j]이다.

// k <= K[i][j]에 대해 dp[i][k - 1] < dp[k + 1][j] <= dp[k + 1][j + 1]이므로
// K[i][j] <= K[i][j + 1]

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
ll dp[MAXN][MAXN];
int opt[MAXN][MAXN];

void init() {}

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

void f() {
    for (int i = 1; i <= n; i++) dp[i][i] = a[i];
    for (int len = 2; len <= n; len++) {
        int prv = 1;
        for (int l = 1, r = len; r <= n; l++, r++) {
            for (int opt = prv; dp[l][opt - 1] < dp[opt + 1][r])
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

        cout << flush;
    }
}