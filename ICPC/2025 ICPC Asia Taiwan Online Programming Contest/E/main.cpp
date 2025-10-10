#include <bits/stdc++.h>
using namespace std;

const int N = 505;
const int M = 505;
const int dy[] = {1, -1, 0, 0};
const int dx[] = {0, 0, 1, -1};

int n, m, k;
int a[N][M];
int y_st, x_st, y_en, x_en;

bool vis[N][M];

void dfs(int y, int x, int &cnt0, const int ub) {
    if (!a[y][x] && !(y_st <= y && y <= y_en && x_st <= x && x <= x_en)) cnt0++;

    for (int d = 0; d < 4; d++) {
        int ny = y + dy[d], nx = x + dx[d];
        if (ny < 1 || n < ny || nx < 1 || m < nx) continue;
        if (vis[ny][nx]) continue;
        if (ub < a[ny][nx]) continue;
        vis[ny][nx] = 1;
        dfs(ny, nx, cnt0, ub);
    }
}

bool f(const int ub) {
    int cnt_need_move = 0;
    for (int y = y_st; y <= y_en; y++) {
        for (int x = x_st; x <= x_en; x++) {
            if (a[y][x] > ub) return 0;

            if (a[y][x]) cnt_need_move++;
        }
    }

    memset(vis, 0, sizeof(vis));

    int cnt0 = 0;
    dfs(y_st, x_st, cnt0, ub);
    return cnt0 >= cnt_need_move;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 1; i <= k; i++) {
        int y, x;
        cin >> y >> x;
        a[y][x] = i;
    }
    cin >> y_st >> x_st >> y_en >> x_en;

    int l = 0, r = k + 1;
    while (l < r) {
        int mid = (l + r) >> 1;

        if (f(mid)) r = mid;
        else l = mid + 1;
    }

    cout << (l == k + 1 ? -1 : l);
}
