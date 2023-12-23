#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10101;
const int INF = 1e9 + 7;

const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

int n, m;
int a[3][MAXN];
int vi[3][MAXN];

void init() {
    memset(a, 0, sizeof(a));
    memset(vi, 0, sizeof(vi));
}

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[1][i];
    for (int i = 1; i <= n; i++) cin >> a[2][i];
}

pair<int, int> dfs(int y, int x) {
    vi[y][x] = 1;

    pair<int, int> ret;
    for (int d = 0; d < 4; d++) {
        int ny = y + dy[d], nx = x + dx[d];
        if (ny < 1 || 2 < ny || nx < 1 || n < nx) continue;
        if (vi[ny][nx]) continue;
        if (a[y][x] + a[ny][nx] > m) continue;
        pair<int, int> res = dfs(ny, nx);
        ret.first += res.first;
        ret.second += res.second;
    }
    
    if (ret.second > 0) {
        ret.first += ret.second;
        ret.second = 0;
    }
    else ret.second = 1;

    return ret;
}

int f() {
    int ret = 0;
    for (int i = 1; i <= n; i++) {
        if (!vi[1][i]) {
            pair<int, int> res = dfs(1, i);
            ret += res.first + res.second;
        }
        if (!vi[2][i]) {
            pair<int, int> res = dfs(2, i);
            ret += res.first + res.second;
        }
    }
    return ret;
}

int solve() {
    int ret = f();
    memset(vi, 0, sizeof(vi));

    if (a[1][1] + a[1][n] <= m) {
        vi[1][1] = vi[1][n] = 1;
        ret = min(ret, 1 + f());
    }
    memset(vi, 0, sizeof(vi));

    if (a[2][1] + a[2][n] <= m) {
        vi[2][1] = vi[2][n] = 1;
        ret = min(ret, 1 + f());
    }
    memset(vi, 0, sizeof(vi));

    if (a[1][1] + a[1][n] <= m && a[2][1] + a[2][n] <= m) {
        vi[1][1] = vi[1][n] = 1;
        vi[2][1] = vi[2][n] = 1;
        ret = min(ret, 2 + f());
    }
    memset(vi, 0, sizeof(vi));

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        if (n == 1) {
            cout << (a[1][1] + a[2][1] <= m ? 1 : 2) << '\n';
            continue;
        }

        cout << solve() << '\n';
    }
}