// #pragma GCC optimize ("O3")
// #pragma GCC optimize ("Ofast")
// #pragma GCC optimize ("unroll-loops")
// #pragma GCC target ("avx2")

#include <bits/stdc++.h>
// #include <x86intrin.h>
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
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

const int MAXN = 1010101, MAXK = 1010101;

int n, k;
int a[MAXN];
ll dp[3030][3030][2];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];

    dp[0][0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k + 1; j++) {
            if (j == k) {
                dp[i][j][1] = (dp[i][j][1] + dp[i - 1][j - 1][0]) % MOD;
            }
            else {
                dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j - 1][0]) % MOD;
            }
            dp[i][j][1] = (dp[i][j][1] + dp[i - 1][j - 1][1]) % MOD;
            
            dp[i][0][0] = (dp[i][0][0] + dp[i - 1][j - 1][0]) % MOD;
            dp[i][0][1] = (dp[i][0][1] + dp[i - 1][j - 1][1]) % MOD;
        }
    }

    ll ans = 0;
    for (int i = 0; i <= k; i++) {
        ans = (ans + dp[n][i][1]) % MOD;
    }
    cout << ans;
}
