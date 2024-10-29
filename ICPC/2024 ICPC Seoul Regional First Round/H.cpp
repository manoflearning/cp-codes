#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const vector<pii> ord = {
    {4, 1},
    {4, 2},
    {1, 4},
    {2, 4},
    {3, 3},
    {3, 2},
    {3, 1},
    {2, 3},
    {1, 3},
    {2, 2},
    {1, 2},
    {2, 1},
    {1, 1},
};

vector<vector<ll>> dp(10, vector<ll>(10, -1));
ll ans = 0;
vector<bool> vis(14);

void bt(int i) {
    auto [y, x] = ord[i];
    assert(dp[y][x] == -1);
    int cnt_y = 0, cnt_x = 0;
    for (int yy = 1; yy <= 4; yy++) {
        if (dp[yy][x] == -1) cnt_x++;
    }
    for (int xx = 1; xx <= 4; xx++) {
        if (dp[y][xx] == -1) cnt_y++;
    }
    assert(cnt_x > 0 && cnt_y > 0);

    if (cnt_y == 1 && cnt_x == 1) {
        assert(i == sz(ord) - 1);

        ll res1 = dp[y][0];
        for (int xx = 1; xx <= 4; xx++)
            if (dp[y][xx] != -1) res1 -= dp[y][xx];
        ll res2 = dp[0][x];
        for (int yy = 1; yy <= 4; yy++)
            if (dp[yy][x] != -1) res2 -= dp[yy][x];
        if (res1 != res2) return;
        if (res1 < 1 || 13 < res1) return;
        if (vis[res1]) return;

        // dp[y][x] = res1;
        // for (int i = 1; i <= 4; i++) {
        //     for (int j = 1; j <= 4; j++) {
        //         cout << dp[i][j] << ' ';
        //     }
        //     cout << '\n';
        // }
        // cout << '\n';
        dp[y][x] = -1;

        ans++;
        return;
    } else if (cnt_y == 1) {
        ll res = dp[y][0];
        for (int xx = 1; xx <= 4; xx++)
            if (dp[y][xx] != -1) res -= dp[y][xx];
        if (res < 1 || 13 < res) return;
        if (vis[res]) return;
        dp[y][x] = res;
        vis[res] = 1;
        bt(i + 1);
        dp[y][x] = -1;
        vis[res] = 0;
    } else if (cnt_x == 1) {
        ll res = dp[0][x];
        for (int yy = 1; yy <= 4; yy++)
            if (dp[yy][x] != -1) res -= dp[yy][x];
        if (res < 1 || 13 < res) return;
        if (vis[res]) return;
        dp[y][x] = res;
        vis[res] = 1;
        bt(i + 1);
        dp[y][x] = -1;
        vis[res] = 0;
    } else {
        for (int val = 1; val <= 13; val++) {
            if (vis[val]) continue;
            dp[y][x] = val;
            vis[val] = 1;
            bt(i + 1);
            dp[y][x] = -1;
            vis[val] = 0;
        }
    }
}

int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    assert(sz(ord) == 13);
    
    cin >> dp[0][1] >> dp[0][2] >> dp[0][3] >> dp[0][4];
    cin >> dp[1][0] >> dp[2][0] >> dp[3][0] >> dp[4][0];

    dp[3][4] = dp[4][3] = dp[4][4] = 0;
    bt(0);
    cout << ans;
}
