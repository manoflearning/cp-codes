#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

const int MOD = 1e9 + 7;

int n, m, l;
string s;
vector<string> a;
vector<int> xx[26][303], yy[26][303];

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

const int dy[] = { 1, -1, 1, -1 };
const int dx[] = { 2, -2, -2, 2 };

ll alldir(int len, int y, int x);

ll f(int len, int y, int x, int dir) {
    if (y < 0 || n <= y || x < 0 || m <= x) return 0;

    ll& ret = dp[len][y][x][dir];
    if (ret != -1) return ret;
    if (len == l - 1) return ret = 1;

    ret = 0;
    int nchar = s[len + 1] - 'A';

    ret = (ret + f(len, y + (dy[dir] > 0 ? 1 : -1), x + (dx[dir] > 0 ? 1 : -1), dir)) % MOD;

    int ny = y + dy[dir] + (dy[dir] > 0 ? 1 : -1), nx = x + dx[dir] + (dx[dir] > 0 ? 1 : -1);
    for (int i = 0; i < 2; i++) {
        if (0 <= ny && ny < n) {
            if (dy[dir] > 0) {
                int idx = upper_bound(all(yy[nchar][ny]), nx) - yy[nchar][ny].begin();
                for (int i = idx; i < sz(yy[nchar][ny]); i++) {
                    ret = (ret + alldir(len + 1, ny, yy[nchar][ny][i])) % MOD;
                }
            }
            else {
                int idx = lower_bound(all(yy[nchar][ny]), nx) - yy[nchar][ny].begin();
                for (int i = idx - 1; i >= 0; i--) {
                    ret = (ret + alldir(len + 1, ny, yy[nchar][ny][i])) % MOD;
                }
            }
        }

        if (0 <= nx && nx < m) {
            if (dx[dir] > 0) {
                int idx = upper_bound(all(xx[nchar][nx]), ny) - xx[nchar][nx].begin();
                for (int i = idx; i < sz(xx[nchar][nx]); i++) {
                    ret = (ret + alldir(len + 1, xx[nchar][nx][i], nx)) % MOD;
                }
            }
            else {
                int idx = lower_bound(all(xx[nchar][nx]), ny) - xx[nchar][nx].begin();
                for (int i = idx - 1; i >= 0; i--) {
                    ret = (ret + alldir(len + 1, xx[nchar][nx][i], nx)) % MOD;
                }
            }
        }

        if (0 <= ny && ny < n && 0 <= nx && nx < m) {
            if (a[ny][nx] == s[len + 1]) {
                ret = (ret + alldir(len + 1, ny, nx)) % MOD;
            }
        }

        ny += (dy[dir] > 0 ? 1 : -1), nx -= (dx[dir] > 0 ? 1 : -1);
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
            yy[a[i][j] - 'A'][i].push_back(j);
            xx[a[i][j] - 'A'][j].push_back(i);
        }
    }

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 303; j++) {
            sort(all(yy[i][j]));
            sort(all(xx[i][j]));
        }
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[0] == a[i][j]) {
                ans = (ans + alldir(0, i, j)) % MOD;
            }
        }
    }

    cout << ans;

    return 0;
}

ll alldir(int len, int y, int x) {
    if (len == l - 1) return 1;

    ll ret = 0;
    for (int i = 0; i < 4; i++) {
        ret = (ret + f(len, y, x, i)) % MOD;
    }
    return ret;
}