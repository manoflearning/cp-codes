// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

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
const int MOD = 998244353;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n, a[5050];
deque<ll> dp[5050];
ll sum[5050];
ll ans = 0;

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

void bottomup() {
    for (int j = 1; j <= n; j++)
        dp[j].resize(2);

    // base case
    if (a[1] == -1) {
        for (int j = 1; j <= n; j++)
            dp[j][1] = sum[j] = 1;
    }
    else dp[a[1]][1] = sum[a[1]] = 1;

    // inductive step
    for (int i = 2; i <= n; i++) {
        int x = a[i];

        vector<ll> tmp(n + 1);
        ll tmpall = 0;
        for (int j = 1; j <= n; j++) {
            tmp[j] = sum[j];
            tmpall = (tmpall + sum[j]) % MOD;
        }

        if (x == -1) {
            for (int j = 1; j <= n; j++) {
                dp[j].push_front(0);
                if (j + 1 < sz(dp[j])) {
                    sum[j] = (sum[j] + MOD - dp[j][j + 1]) % MOD;
                    dp[j].resize(j + 1);
                }
            }

            for (int j = 1; j <= n; j++) {
                dp[j][1] = (dp[j][1] + tmpall - tmp[j]) % MOD;
                dp[j][1] = (dp[j][1] + MOD) % MOD;
                sum[j] = (sum[j] + dp[j][1]) % MOD;
            }
        }
        else {
            dp[x].push_front(0);
            if (x + 1 < sz(dp[x])) {
                sum[x] = (sum[x] + MOD - dp[x][x + 1]) % MOD;
                dp[x].resize(x + 1);
            }

            dp[x][1] = (dp[x][1] + tmpall - tmp[x]) % MOD;
            dp[x][1] = (dp[x][1] + MOD) % MOD;
            sum[x] = (sum[x] + dp[x][1]) % MOD;

            for (int j = 1; j <= n; j++) {
                if (x == j) continue;
                dp[j].clear();
                dp[j].resize(2);
                sum[j] = 0;
            }
        }
    }

    // get answer
    for (int j = 1; j <= n; j++) {
        ans = (ans + sum[j]) % MOD;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    bottomup();

    cout << ans;
}