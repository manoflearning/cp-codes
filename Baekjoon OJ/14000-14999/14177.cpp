#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll INF = 1e9 + 7;

int N, K;
ll u[4040][4040];
ll sum[4040][4040];
ll dp[808][4040];

void input() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> u[i][j];
        }
    }
}

void build_sum() {
    for (int len = 2; len <= N; len++) {
        for (int i = 1; i + len - 1 <= N; i++) {
            int j = i + len - 1;
            sum[i][j] += sum[i][j - 1];
            sum[i][j] += sum[i + 1][j];
            sum[i][j] -= sum[i + 1][j - 1];
            sum[i][j] += u[i][j];
        }
    }
}

void f(int gr, int l, int r, int nl, int nr) {
    int mid = (l + r) >> 1, idx = -1;
    ll& res = dp[gr][mid];
    res = INF;
    for (int i = nl; i <= min(mid, nr); i++) {
        ll val = dp[gr - 1][i] + sum[i + 1][mid];
        if (res > val) {
            res = val, idx = i;
        }
    }
    if (l < r) {
        f(gr, l, mid, nl, idx);
        f(gr, mid + 1, r, idx, nr);
    }
}

void solve() {
    // base case
    for (int i = 1; i <= N; i++) {
        dp[1][i] = sum[1][i];
    }
    // inductive step
    for (int i = 2; i <= K; i++) {
        f(i, 1, N, 1, N);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    build_sum();

    solve();

    cout << dp[K][N];
}