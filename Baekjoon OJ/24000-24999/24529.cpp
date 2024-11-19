#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()

int n;
struct Story {
    int f, l;
    bool operator<(const Story &rhs) const {
        return l < rhs.l;
    }
};
vector<Story> a, b, c;
vector<int> d;

int dp[55][55][55][55][3];

void input() {
    cin >> n;
    a.resize(n);
    b.resize(n);
    c.resize(n);
    for (auto &[f, l] : a) cin >> f >> l;
    for (auto &[f, l] : b) cin >> f >> l;
    for (auto &[f, l] : c) cin >> f >> l;
    d.resize(n);
    for (auto &i : d) cin >> i;
}

void bottomup() {
    memset(dp, -1, sizeof(dp));
    
    // base case
    dp[0][0][0][0][0] = dp[0][0][0][0][1] = dp[0][0][0][0][2] = 0;

    // inductive step
    for (int idx = 0; idx < n; idx++) {
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                for (int k = 0; k <- n; k++) {
                    for (int p = 0; p < 3; p++) {
                        if (dp[idx][i][j][k][p] == -1) continue;

                        if (p != 0)
                        for (int ii = i; ii < n; ii++) {
                            if (a[ii].l > d[idx]) break;
                            dp[idx + 1][ii + 1][j][k][0] = max(dp[idx + 1][ii + 1][j][k][0], dp[idx][i][j][k][p] + a[ii].f);
                        }

                        if (p != 1)
                        for (int jj = j; jj < n; jj++) {
                            if (b[jj].l > d[idx]) break;
                            dp[idx + 1][i][jj + 1][k][1] = max(dp[idx + 1][i][jj + 1][k][1], dp[idx][i][j][k][p] + b[jj].f);
                        }

                        if (p != 2)
                        for (int kk = k; kk < n; kk++) {
                            if (c[kk].l > d[idx]) break;
                            dp[idx + 1][i][j][kk + 1][2] = max(dp[idx + 1][i][j][kk + 1][2], dp[idx][i][j][k][p] + c[kk].f);
                        }
                    }
                }
            }
        }
    }
    

    // get answer
    int ans = -1;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= n; k++) {
                for (int p = 0; p < 3; p++) {
                    ans = max(ans, dp[n][i][j][k][p]);
                }
            }
        }
    }
    cout << ans;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    sort(all(a));
    sort(all(b));
    sort(all(c));

    bottomup();
}
