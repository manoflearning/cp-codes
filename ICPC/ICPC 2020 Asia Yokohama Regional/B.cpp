#include <bits/stdc++.h>
using namespace std;

int n, m, a[121], b[121];
int dp[121][121];

int ansa[121], ansb[121];

int f(int i, int j) {
    int& ret = dp[i][j];
    if (ret != -1) return ret;
    if (i == n + 1 && j == m + 1) return ret = 1;

    ret = 0;
    int x = i + j - 1;
    if (i <= n && j <= m) {
        if (a[i] == x || a[i] == 0) ret |= f(i + 1, j);
        if (b[j] == x || b[j] == 0) ret |= f(i, j + 1);
    }
    else if (i <= n) {
        if (a[i] == x || a[i] == 0) ret |= f(i + 1, j);
        else ret |= 0;
    }
    else if (j <= m) {
        if (b[j] == x || b[j] == 0) ret |= f(i, j + 1);
        else ret |= 0;
    }
    return ret;
}

void rf(int i, int j) {
    int x = i + j - 1;
    if (i <= n && j <= m) {
        if (a[i] == x || a[i] == 0) {
            if (f(i + 1, j)) {
                ansa[i] = x;
                rf(i + 1, j);
                return;
            }
        }
        if (b[j] == x || b[j] == 0) {
            if (f(i, j + 1)) {
                ansb[j] = x;
                rf(i, j + 1);
                return;
            }
        }
    }
    else if (i <= n) {
        if (a[i] == x || a[i] == 0) {
            if (f(i + 1, j)) {
                ansa[i] = x;
                rf(i + 1, j);
                return;
            }
        }
    }
    else if (j <= m) {
        if (b[j] == x || b[j] == 0) {
            if (f(i, j + 1)) {
                ansb[j] = x;
                rf(i, j + 1);
                return;
            }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> b[i];

    memset(dp, -1, sizeof(dp));

    rf(1, 1);

    for (int i = 1; i <= n; i++) cout << ansa[i] << ' ';
    cout << '\n';
    for (int i = 1; i <= m; i++) cout << ansb[i] << ' ';
    cout << '\n';
}