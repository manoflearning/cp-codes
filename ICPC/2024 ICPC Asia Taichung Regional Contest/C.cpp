#include <bits/stdc++.h>
using namespace std;
#define ll long long

const ll INF = 1e18;

int n, a[12][12][12];
ll dp[1 << 12][1 << 12];

ll f(int z, int bitx, int bity) {
    ll &ret = dp[bitx][bity];
    if (ret != -1) return ret;
    if (z == n) return ret = 0;

    ret = INF;
    for (int x = 0; x < n; x++) {
        if (bitx & (1 << x)) continue;
        for (int y = 0; y < n; y++) {
            if (bity & (1 << y)) continue;
            ret = min(ret, a[x][y][z] + f(z + 1, bitx | (1 << x), bity | (1 << y)));
        }
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

    memset(dp, -1, sizeof(dp));

    cin >> n;
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            for (int z = 0; z < n; z++) {
                cin >> a[x][y][z];
            }
        }
    }

    cout << f(0, 0, 0);
}
