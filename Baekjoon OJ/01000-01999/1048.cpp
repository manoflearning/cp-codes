#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1e9 + 7;

struct Point {
    int y, x;
};

int n, m, l;
string s;
vector<string> a;
vector<Point> xx[26][303], yy[26][303];

ll dp[55][303][303][4];

void init() {
    for (int i = 0; i < 55; i++) {
        for (int j = 0; j < 303; j++) {
            for (int k = 0; k < 303; k++) {
                dp[i][j][k][0] = dp[i][j][k][1] = dp[i][j][k][2] = dp[i][j][k][3] = -1;
            }
        }
    }
}

void input() {
    cin >> n >> m >> l;
    cin >> s;
    a.resize(n);
    for (auto& i : a) cin >> i;
}

const int dy[] = { 1, -1, 2, -2 };
const int dx[] = { 2, -2, 1, -1 };

ll f(int len, int y, int x, int dir) {
    if (y < 0 || n <= y || x < 0 || m <= x) return 0;

    ll& ret = dp[len][y][x][dir];
    if (ret != -1) return ret;
    if (len == l - 1) return ret = 1;

    ret = 0;

    if (dir == 0) {
        ret = (ret + f(len, y + 1, x + 1, dir)) % MOD;
        
        int ny = y + 2;
        if (ny )
        for (auto& i : yy[ny])
    }

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    init();

    input();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            yy[a[i][j] - 'A'][i].push_back({ i, j });
            xx[a[i][j] - 'A'][j].push_back({ i, j });
        }
    }

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 303; j++) {
            sort(yy[i][j].begin(), yy[i][j].end());
            sort(xx[i][j].begin(), xx[i][j].end());
        }
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[0] == a[i][j]) {
                ans = (ans + f(0, i, j, 0)) % MOD;
                ans = (ans + f(0, i, j, 1)) % MOD;
                ans = (ans + f(0, i, j, 2)) % MOD;
                ans = (ans + f(0, i, j, 3)) % MOD;
            }
        }
    }

    cout << ans;

    return 0;
}