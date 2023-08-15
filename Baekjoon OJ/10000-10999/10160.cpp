//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1'000'000'009;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n, k;
ll dp[1010101][12];
// dp[i][j]는 [1, i]에서 [i - j + 1, i]가 특정 패턴의 접두사와 일치하는 경우의 수.

ll powxy(ll x, ll y) {
    if (y == 0) return 1;
    if (y == 1) return x;
    ll res = powxy(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;
    dp[0][0 << 1] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i][0 << 1] += (k - 1) * dp[i - 1][0 << 1]; // A 제외
        dp[i][1 << 1] += dp[i - 1][0 << 1]; // A

        dp[i][0 << 1] += (k - 2) * dp[i - 1][1 << 1]; // A, B 제외
        dp[i][1 << 1] += dp[i - 1][1 << 1]; // A
        dp[i][2 << 1] += dp[i - 1][1 << 1]; // B

        dp[i][0 << 1] += (k - 2) * dp[i - 1][2 << 1]; // A, C 제외
        dp[i][3 << 1 | 1] += dp[i - 1][2 << 1]; // A
        dp[i][3 << 1] += dp[i - 1][2 << 1]; // C

        dp[i][0 << 1] += (k - 2) * dp[i - 1][3 << 1]; // A, B 제외
        dp[i][1 << 1] += dp[i - 1][3 << 1]; // A
        dp[i][4 << 1] += dp[i - 1][3 << 1]; // B

        dp[i][0 << 1] += (k - 2) * dp[i - 1][3 << 1 | 1]; // A, B 제외
        dp[i][1 << 1] += dp[i - 1][3 << 1 | 1]; // A
        dp[i][4 << 1 | 1] += dp[i - 1][3 << 1 | 1]; // B
        
        dp[i][0 << 1] += (k - 2) * dp[i - 1][4 << 1]; // A, C 제외
        dp[i][1 << 1] += dp[i - 1][4 << 1]; // A

        dp[i][0 << 1] += (k - 2) * dp[i - 1][4 << 1 | 1]; // A, C 제외
        dp[i][3 << 1 | 1] += dp[i - 1][4 << 1 | 1]; // A

        for (int j = 0; j < 10; j++) dp[i][j] %= MOD;
    }

    ll ans = 0;
    for (int i = 0; i < 10; i++)
        ans = (ans + dp[n][i]) % MOD;

    cout << ans;
}