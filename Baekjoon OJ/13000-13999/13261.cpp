// Divide and Conquer Optimization 
// Recurrence: dp[t][i] = min(dp[t - 1][j] + c[j][i]) (j < i)
// Condition: Let opt[t][i] be j with the smallest value of dp[t - 1][j] + c[j][i]. It must satisfy opt[t][i] <= opt[t][i + 1].
// Naive Complexity: O(m * n^2)
// Optimized Complexity: O(m * nlogn)

// BOJ 13261 AC Code
// https://www.acmicpc.net/problem/13261
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll INF = 1e18;
int n, m;
ll a[8080], psum[8080];
ll dp[808][8080];
void f(int gr, int l, int r, int nl, int nr) {
    int mid = (l + r) >> 1, idx = -1;
    ll& res = dp[gr][mid];
    res = INF;
    for (int i = nl; i <= min(mid, nr); i++) {
        assert(i <= mid);
        ll val = dp[gr - 1][i] + (mid - i) * (psum[mid] - psum[i]);
        if (res > val) {
            res = val, idx = i;
        }
    }
    if (l < r) {
        f(gr, l, mid, nl, idx);
        f(gr, mid + 1, r, idx, nr);
    }
}

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // input
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];

    // build prefix sum
    for (int i = 1; i <= n; i++) 
        psum[i] = a[i] + psum[i - 1];

    // dp (dnc opt)
    for (int i = 1; i <= n; i++)
        dp[1][i] = i * psum[i];

    for (int i = 2; i <= m; i++)
        f(i, 0, n, 0, n);

    // output
    cout << dp[m][n];
}