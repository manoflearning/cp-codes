#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll INF = 1e18;

int n, q;
char h[3030];
ll t[3030];

ll dp[3030][3030];

bool is_contain(int x, int y, int z) {
    if (x <= z) return x <= y && y <= z;
    else return x <= y || y <= z;
}

ll cal(int x, int y) {
    if (x <= y) return y - x;
    else return n - x + y;
}

void move(int i, int l1, int l2, int prv, int en) {
    // cw
    if (is_contain(l1, l2, en)) {
        dp[i][(en + 1) % n] = min(dp[i][(en + 1) % n], cal(l2, (en + 1) % n) + cal(l1, en) + dp[i - 1][prv]);
    } else {
        dp[i][l2] = min(dp[i][l2], cal(l1, en) + dp[i - 1][prv]);
    }
    // ccw
    if (is_contain(en, l2, l1)) {
        dp[i][(en + n - 1) % n] = min(dp[i][(en + n - 1) % n], cal((en + n - 1) % n, l2) + cal(en, l1) + dp[i - 1][prv]);
    } else {
        dp[i][l2] = min(dp[i][l2], cal(en, l1) + dp[i - 1][prv]);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    for (int i = 1; i < 3030; i++)
        for (int j = 0; j < 3030; j++) dp[i][j] = INF;

    cin >> n >> q;

    for (int i = 1; i <= q; i++) {
        cin >> h[i] >> t[i];
        t[i]--;
    }

    // base case
    if (h[1] == 'L') move(1, 0, 1, 0, t[1]);
    if (h[1] == 'R') move(1, 1, 0, 0, t[1]);

    // inductive step
    for (int i = 2; i <= q; i++) {
        if (h[i - 1] == 'L') {
            int pl1 = t[i - 1];
            for (int pl2 = 0; pl2 < n; pl2++) {
                if (dp[i - 1][pl2] == INF) continue;

                if (h[i] == 'L') move(i, pl1, pl2, pl2, t[i]);
                if (h[i] == 'R') move(i, pl2, pl1, pl2, t[i]);
            }
        }
        if (h[i - 1] == 'R') {
            int pl2 = t[i - 1];
            for (int pl1 = 0; pl1 < n; pl1++) {
                if (dp[i - 1][pl1] == INF) continue;

                if (h[i] == 'L') move(i, pl1, pl2, pl1, t[i]);
                if (h[i] == 'R') move(i, pl2, pl1, pl1, t[i]);
            }
        }
    }

    // for (int i = 1; i <= q; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << i << ' ' << j << ' ' << dp[i][j] << '\n';
    //     }
    //     cout << '\n';
    // }

    ll ans = INF;
    for (int i = 0; i < 3030; i++)
        ans = min(ans, dp[q][i]);
    cout << ans;
}
