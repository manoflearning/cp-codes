#include <bits/stdc++.h>
using namespace std;
#define ll long long

int gn[121][121];

int f(int y, int x, int n, int m, int k) {
    int &ret = gn[y][x];
    if (y == n && x == m) return ret = 0;

    vector<int> vis(33);
    if (y < n) vis[f(y + 1, x, n, m, k)] = 1;
    if (x < m) vis[f(y, x + 1, n, m, k)] = 1;
    if (y + k <= n && x + k <= m) vis[f(y + k, x + k, n, m, k)] = 1;

    for (int i = 0; i < 33; i++)
        if (!vis[i]) return ret = i;
    assert(0);
}

bool solve(ll n, ll m, ll k) {
    ll cnt = min(n, m) / (k + 1);

    bool ret = 0;
    if (cnt > 0) {
        if (min(n, m) % (k + 1) == 0) ret = 1;
        else {
            if (k > 1) if ((n + m + cnt) & 1) ret = 1;
            if (k == 1) if ((n + m) & 1) ret = 1;
        }
    } else {
        if ((n + m) & 1) ret = 1;
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    // for (int n = 1; n <= 10; n++) {
    //     for (int m = 1; m <= 10; m++) {
    //         for (int k = 1; k <= 10; k++) {
    //             memset(gn, -1, sizeof(gn));

    //             int res1 = f(1, 1, n, m, k) ? 1 : 0;
    //             int res2 = solve(n, m, k);
                
    //             if (res1 != res2) {
    //                 cout << "n = " << n << ", " << "m = " << m << ", " << "k = " << k << '\n';
    //                 for (int y = 1; y <= n; y++) {
    //                     for (int x = 1; x <= m; x++) {
    //                         int res = (f(y, x, n, m, k) ? 1 : 0);
    //                         cout << res << ' ';
    //                     }
    //                     cout << '\n';
    //                 }
    //                 cout << '\n';

    //                 for (int y = 1; y <= n; y++) {
    //                     for (int x = 1; x <= m; x++) {
    //                         int res = solve(n - y + 1, m - x + 1, k);
    //                         cout << res << ' ';
    //                     }
    //                     cout << '\n';
    //                 }
    //                 cout << '\n';

    //                 assert(0);
    //             }
    //         }
    //     }
    // }

    int tc; cin >> tc;
    while (tc--) {
        ll k, n, m;
        cin >> k >> n >> m;

        cout << (solve(n, m, k) ? "koosaga" : "cubelover") << '\n';
    }
}
