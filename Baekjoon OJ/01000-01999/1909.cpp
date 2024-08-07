#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAX = 1010;
const int INF = 1e9 + 7;

const int dy[] = { 0, -1, -1, -1, 0, 1, 1, 1, 0 };
const int dx[] = { -1, -1, 0, 1, 1, 1, 0, -1, -1 };

struct Point { ll y, x; };

int mxy, mxx;
int sy, sx, ey, ex;

int n;
vector<Point> p;

void input() {
    cin >> mxy >> mxx;
    cin >> sy >> sx >> ey >> ex;
    cin >> n;
    p.resize(n);
    for (auto& i : p) cin >> i.y >> i.x;
}

ll dp[MAX][MAX];
Point dp1[MAX][MAX], dp2[MAX][MAX];
Point dp3[MAX][MAX], dp4[MAX][MAX];

ll calDist(const Point& u, const Point& v) {
    return (u.x - v.x) * (u.x - v.x) + (u.y - v.y) * (u.y - v.y);
}

void buildDP() {
    // initialize
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            dp1[i][j] = { INF, INF };
            dp2[i][j] = { INF, INF };
            dp3[i][j] = { INF, INF };
            dp4[i][j] = { INF, INF };
            dp[i][j] = INF;
        }
    }

    // base case
    for (auto& i : p) {
        dp1[i.y][i.x] = i;
        dp2[i.y][i.x] = i;
        dp3[i.y][i.x] = i;
        dp4[i.y][i.x] = i;
    }

    // inductive step
    for (int y = 1; y <= mxy; y++) {
        for (int x = 1; x <= mxx; x++) {
            Point now = { y, x };
            for (int i = 0; i < 3; i++) {
                int ny = y + dy[i], nx = x + dx[i];
                if (ny < 1 || nx < 1 || mxy < ny || mxx < nx) continue;
                ll res1 = calDist(dp1[y][x], now);
                ll res2 = calDist(dp1[ny][nx], now);
                if (res1 > res2) dp1[y][x] = dp1[ny][nx];
            }
        }
    }

    for (int y = 1; y <= mxy; y++) {
        for (int x = mxx; x >= 1; x--) {
            Point now = { y, x };
            for (int i = 2; i < 5; i++) {
                int ny = y + dy[i], nx = x + dx[i];
                if (ny < 1 || nx < 1 || mxy < ny || mxx < nx) continue;
                ll res1 = calDist(dp2[y][x], now);
                ll res2 = calDist(dp2[ny][nx], now);
                if (res1 > res2) dp2[y][x] = dp2[ny][nx];
            }
        }
    }

    for (int y = mxy; y >= 1; y--) {
        for (int x = mxx; x >= 1; x--) {
            Point now = { y, x };
            for (int i = 4; i < 7; i++) {
                int ny = y + dy[i], nx = x + dx[i];
                if (ny < 1 || nx < 1 || mxy < ny || mxx < nx) continue;
                ll res1 = calDist(dp3[y][x], now);
                ll res2 = calDist(dp3[ny][nx], now);
                if (res1 > res2) dp3[y][x] = dp3[ny][nx];
            }
        }
    }

    for (int y = mxy; y >= 1; y--) {
        for (int x = 1; x <= mxx; x++) {
            Point now = { y, x };
            for (int i = 6; i < 9; i++) {
                int ny = y + dy[i], nx = x + dx[i];
                if (ny < 1 || nx < 1 || mxy < ny || mxx < nx) continue;
                ll res1 = calDist(dp4[y][x], now);
                ll res2 = calDist(dp4[ny][nx], now);
                if (res1 > res2) dp4[y][x] = dp4[ny][nx];
            }
        }
    }

    // get dp
    for (int y = 1; y <= mxy; y++) {
        for (int x = 1; x <= mxx; x++) {
            Point now = { y, x };
            dp[y][x] = min(dp[y][x], calDist(dp1[y][x], now));
            dp[y][x] = min(dp[y][x], calDist(dp2[y][x], now));
            dp[y][x] = min(dp[y][x], calDist(dp3[y][x], now));
            dp[y][x] = min(dp[y][x], calDist(dp4[y][x], now));
        }
    }
}

int ans;

bool bfs(int ub) {
    if (dp[sy][sx] < ub) return 0;

    vector<vector<bool>> vi(MAX, vector<bool>(MAX));

    queue<Point> q;
    q.push({ sy, sx });
    vi[sy][sx] = 1;

    while (!q.empty()) {
        auto [y, x] = q.front();
        q.pop();

        for (int i = 0; i < 8; i += 2) {
            int ny = y + dy[i], nx = x + dx[i];
            if (ny < 1 || mxy < ny || nx < 1 || mxx < nx) continue;
            if (vi[ny][nx]) continue;
            if (dp[ny][nx] < ub) continue;
            q.push({ ny, nx });
            vi[ny][nx] = 1;
        }
    }
    return vi[ey][ex];
}

void bs() {
    int l = 0, r = 2'000'000;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (bfs(mid)) l = mid;
        else r = mid - 1;
    }
    ans = l;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    buildDP();

    bs();

    cout << ans;
}