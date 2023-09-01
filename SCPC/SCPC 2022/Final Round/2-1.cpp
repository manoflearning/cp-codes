// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

int flag;
struct Seg {
    vector<ll> t;
    void build(int n) {
        t.clear();
        for (flag = 1; flag < n; flag <<= 1) t.resize(flag << 1);
    }
    void modify(int p, ll val) {
        
    }
}seg;

const int MAXN = 3030;

int n;
ll a[MAXN];
// ll psum[MAXN];
ll dp[MAXN][MAXN], dp1[MAXN][MAXN], dp2[MAXN][MAXN];

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
        dp1[i][i] = a[i] + a[i + 1];
        dp2[i][i] = a[i] + a[i - 1];
        
        dp1[i][i - 1] = a[i];
        dp2[i + 1][i] = a[i];
    }
    
    // inductive step
    for (int len = 2; len <= n; len++) {
        for (int l = 1; ; l++) {
            int r = l + len - 1;
            if (r > n) break;

            dp[l][r] = 0;
            for (int i = l; i <= r; i++) {
                dp[l][r] = max(dp[l][r], min(dp1[l][i - 1], dp2[i + 1][r]));
            }
            dp1[l][r] = dp[l][r] + a[r + 1];
            dp2[l][r] = dp[l][r] + a[l - 1];
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
