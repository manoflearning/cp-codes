#include <bits/stdc++.h>
using namespace std;

int h, w;
vector<string> a;

int dp[22][22][22][22];
int f(int x1, int y1, int x2, int y2) {
    // base case
    if (x1 > x2 || y1 > y2) return 0;

    auto& ret = dp[x1][y1][x2][y2];
    if (ret != -1) return ret;

    // inductive step
    vector<int> vis(111);
    for (int i = x1; i <= x2; i++) {
        for (int j = y1; j <= y2; j++) {
            if (a[i][j] == 'X') continue;

            int res = 0;
            res ^= f(x1, y1, i - 1, j - 1);
            res ^= f(x1, j + 1, i - 1, y2);
            res ^= f(i + 1, y1, x2, j - 1);
            res ^= f(i + 1, j + 1, x2, y2);

            vis[res] = 1;
        }
    }

    for (int i = 0; ; i++) {
        if (vis[i]) continue;
        return ret = i;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    memset(dp, -1, sizeof(dp));

    cin >> h >> w;
    a.resize(h);
    for (auto& i : a) cin >> i;

    cout << (f(0, 0, h - 1, w - 1) ? "First" : "Second");
}
