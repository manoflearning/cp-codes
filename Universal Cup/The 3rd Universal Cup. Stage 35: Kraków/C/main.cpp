#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 3030;
const int M = 3030;

enum class dir {
    none = 0,
    down = 1,
    right = 2,
};

int n, m;
int d[N][M];

ll dp[N][M][3][2];

void init() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            memset(dp[i][j], -1, sizeof(dp[i][j]));
        }
    }
}

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> d[i][j];
        }
    }
}

ll f(int y, int x, dir prv_dir, int genie) {
    ll &ret = dp[y][x][(int)prv_dir][genie];
    if (ret != -1) return ret;
    if (y == n && x == m) return ret = d[y][x];

    if (genie == 0) { // haven't use genie
        // no genie
        if (y + 1 <= n) ret = max(ret, f(y + 1, x, dir::down, genie));
        if (x + 1 <= m) ret = max(ret, f(y, x + 1, dir::right, genie));

        // using genie
        if (1 <= x - 1) {
            if (y + 1 <= n) ret = max(ret, (prv_dir != dir::right) * d[y][x - 1] + f(y + 1, x - 1, dir::down, 1));
            if (x + 1 <= m) ret = max(ret, (prv_dir != dir::right) * d[y][x - 1] + f(y, x + 1, dir::right, 1));
        }
    } if (genie == 1) { // finished using genie
        if (y + 1 <= n) ret = max(ret, f(y + 1, x, dir::down, genie));
        if (x + 1 <= m) ret = max(ret, f(y, x + 1, dir::right, genie));
    }

    ret += d[y][x];

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    n = N - 1, m = M - 1;

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        cout << f(1, 1, dir::none, 0) << '\n';
    }
}
