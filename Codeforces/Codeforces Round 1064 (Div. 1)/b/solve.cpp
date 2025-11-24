#include <bits/stdc++.h>
using ll = long long;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
using namespace std;

constexpr int MOD = 998'244'353;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> b(n + 1);
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            b[x]++;
        }

        sort(all(b));
        b.erase(b.begin(), lower_bound(all(b), 1));

        vector<ll> dp(n + 1);

        // base case
        dp[0] = 1;

        // inductive step
        int sumx = 0;
        for (auto &x : b) {
            for (int i = sumx; i >= 0; i--) {
                dp[i + x] = (dp[i + x] + x * dp[i]) % MOD;
            }
            sumx += x;
        }

        ll ans = 0;
        for (int i = b[sz(b) - 1]; i <= n; i++) {
            ans = (ans + dp[i]) % MOD;
        }
        cout << ans << '\n';
    }
}

// pick x (in {ai}) y times
// 0 <= y <= b[x]
// ans = mul(b[x] + 1) - 1? (NO)

// if b[x] > k => always need to pick x

// dp[i][j] =
// modes에 속하는 모든 값 x에서 대해 modes 용도로 x 값을 총 i개 사용하고, 
// {s} == j일 때 가능한 경우의 수

// p = (b[x] > i ? 1부터 b[x]까지 : 0부터 b[x]까지)
// dp[i + p][j + p] += dp[i][j]
// TC: O(n^3) (...)
// ans = sum dp[i][j]

// if k == 1 => ans += |modes(x1)|
// if k == 2 => ans 
// - Suppose a[0] is in x1
// 
// ...
// if k == n => ans += 1