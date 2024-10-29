#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second

const int dy[] = {0, 1, 0, -1};
const int dx[] = {1, 0, -1, 0};

const int MAXR = 12117, MAXC = 12117;

int r, c;
bool vis[MAXR][MAXC];

int f1(int y, int x, int len) {
    if (len == 4) return 1;
    int ret = 0;
    for (int d = 0; d < 4; d++) {
        int ny = y + dy[d], nx = x + dx[d];
        if (ny < 0 || r <= ny || nx < 0 || c <= nx) continue;

        int id = (ny * c + nx) % 5;
        if ((len == 2) != (id == 0 || id == 3)) continue;
        if (vis[ny][nx]) continue;

        if (len == 3) ret++;
        else {
            vis[ny][nx] = 1;
            ret += f1(ny, nx, len + 1);
            vis[ny][nx] = 0;
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

    cin >> r >> c;

    ll ans = 0;
    for (int y = 0; y < r; y++) {
        for (int x = 0; x < c; x++) {
            int id = (y * c + x) % 5;
            if (id == 0 || id == 3) ans += f1(y, x, 0);
        }
    }
    cout << ans;

    // if (r <= 100 && c <= 100) {
    //     for (int y = 0; y < r; y++) {
    //         for (int x = 0; x < c; x++) {
    //             int id = (y * c + x) % 5;
    //             a[y][x] = {(id == 0 || id == 3 ? 0 : 1), id};
    //         }
    //     }
    //     ll ans = 0;
    //     for (int y = 0; y < r; y++)
    //         for (int x = 0; x < c; x++)
    //             if (a[y][x].fr == 0) ans += f1(y, x, 0);
    //     cout << ans;
    //     return 0;
    // }

    // int i = 0;
    // for (int y = 0; y < 90 + (r % 5); y++) {
    //     for (int x = 0; x < 90 + (c % 5); x++) {
    //         a[y][x] = {(i == 0 || i == 3 ? 0 : 1), i};
    //         i = (i + 1) % 5;
    //     }
    // }

    // ll ans1 = 0, ans2 = 0;

    // // 가장자리까지의 맨해튼 거리의 최소가 4 이상인 좌표:
    // // 일반화하여 2가지 경우의 수 중 하나로 분류:
    // // - "뚜"루루뚜루
    // // - 뚜루루"뚜"루    
    // for (int x = 4; x <= 90; x++) {
    //     if (a[4][x].sc == 0) {
    //         ans1 = f1(4, x, 0);
    //         ans2 = f1(4, x + 3, 0);
    //         break;
    //     }
    // }
    // // 가장자리까지의 맨해튼 거리의 최소가 4 미만인 좌표:
    // // - (1, 1) ~ (4, 4)
    // // - (1, c-3) ~ (4, c)
    // // - (r-3, 1) ~ (r, 4)
    // // - (r-3, c-3) ~ (r, c)
    // // - (1, 5) ~ (5, c-4)
    // // - (5, 1) ~ (r-4, 5)
    // // - (r-3, 5) ~ (r, c-4)
    // // - (5, c-3) ~ (c-4, c)
}
