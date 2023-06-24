#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

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
const ll INF = 1e18;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n, k;
ll w;
map<pii, ll> a;
ll all[202020];

void input() {
    cin >> n >> k >> w;
    for (int i = 0; i < n; i++) {
        int x, y, c;
        cin >> x >> y >> c;
        a[{ x, y }] = c;
        all[x] += c;
    }
}

ll dp[2][202020];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    // naive
    // dp[x][y]는 0 <= x_i <= x인 모든 점들을 삭제했을 때 비용의 최솟값.
    // 마지막 삼각형의 yco = y임을 의미. 단 yco = k라면 삼각형을 설치하지 않은 것.

    // base case
    ll rem = all[0];
    dp[0][k] = rem;
    for (int y = k - 1; y >= 0; y--) {
        if (a.count({ 0, y })) rem -= a[{ 0, y }];
        dp[0][y] = rem + (k - (0 + y)) * w;
    }

    // inductive step
    for (int x = 1; x < k; x++) {
        int b = (x & 1);
        ll prv = INF;

        rem = all[x];
        for (int y = k; y > k - x - 1; y--) {
            dp[b][y] = rem + dp[!b][y];
            prv = min(prv, dp[!b][y]);
        }
        
        for (int y = k - x - 1; y >= 0; y--) {
            if (a.count({ x, y })) rem -= a[{ x, y }];
            dp[b][y] = min(rem + dp[!b][y], prv + rem + (k - (x + y)) * w);
            prv = min(prv, dp[!b][y]);
        }
    }

    // output
    ll ans = INF;
    for (int y = 0; y <= k; y++)
        ans = min(ans, dp[(k - 1) & 1][y]);

    cout << ans;
}