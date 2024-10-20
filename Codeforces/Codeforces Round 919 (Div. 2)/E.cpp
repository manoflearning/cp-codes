// string s = "...00100..."
// n = (# zeros left) * (# zeros right)

// string s = "...111..."
// n = (# ones)

// integer array a = { # zeros_1, # zeros_2, ... }
// n = sum[(# zeros_{i} + 1) * (# zeros_{i + 1} + 1)]
// (# zeros_{i}) + (# zeros_{i + 1}) < k

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
const int MOD = 998'244'353;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n, k;

void init() {

}

void input() { cin >> n >> k; }

void naive() {
    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1));
    // dp[# good substrings][rightmost # zeros] = possible counts

    // base case
    for (int i = 0; i < k; i++) {
        dp[0][i] = 1;
    }

    // inductive step
    for (int i = 1; i <= n; i++) { // O(n^2 * sqrt(n))
        for (int j = 0; j < k; j++) {
            for (int t = 0; t + j < k; t++) {
                if (i < (t + 1) * (j + 1)) break;
                dp[i][j] = (dp[i][j] +
                dp[i - (t + 1) * (j + 1)][t]) % MOD;
            }
        }
    }

    ll ans = 0;
    for (int i = 0; i <= n; i++)
        ans = (ans + dp[n][i]) % MOD;
    cout << ans << '\n';
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        init();

        input();

        naive();
    }
}