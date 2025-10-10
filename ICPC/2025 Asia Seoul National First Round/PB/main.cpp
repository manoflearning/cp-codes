#include <bits/stdc++.h>
using namespace std;

const int M = 13;
const int ordy[] = {4, 4, 2, 1, 3, 3, 3, 2, 1, 2, 2, 1, 1};
const int ordx[] = {2, 1, 4, 4, 3, 2, 1, 3, 3, 2, 1, 2, 1};

int ans = 0;
int a[5][5];
bool vis[M + 1];

void bt(int idx) {
    if (idx == M) {
        ans++;
        return;
    }

    // if idx == 1, 3, 6, 8, 10, 11, 12

    int y = ordy[idx], x = ordx[idx];
    if (idx == 0 || idx == 2 || idx == 4 || idx == 5 || idx == 7 || idx == 9) {
        for (int i = 1; i <= M; i++) {
            if (vis[i]) continue;

            vis[i] = 1;
            a[y][x] = i;

            bt(idx + 1);

            vis[i] = 0;
            a[y][x] = 0;
        }
    } else {
        int val = -1;
        if (idx == 1) {
            val = a[4][0] - a[4][2];
        } else if (idx == 3) {
            val = a[0][4] - a[2][4];
        } else if (idx == 6) {
            val = a[3][0] - (a[3][2] + a[3][3]);
        } else if (idx == 8) {
            val = a[0][3] - (a[2][3] + a[3][3]);
        } else if (idx == 10) {
            val = a[2][0] - (a[2][2] + a[2][3] + a[2][4]);
        } else if (idx == 11) {
            val = a[0][2] - (a[2][2] + a[3][2] + a[4][2]);
        } else if (idx == 12) {
            int val1 = a[0][1] - (a[2][1] + a[3][1] + a[4][1]);
            int val2 = a[1][0] - (a[1][2] + a[1][3] + a[1][4]);
            if (val1 != val2) return;
            val = val1;
        } else assert(0);

        if (val < 1 || M < val || vis[val]) return;
        
        vis[val] = 1;
        a[y][x] = val;
        
        bt(idx + 1);

        vis[val] = 0;
        a[y][x] = 0;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 1; i <= 4; i++) cin >> a[0][i];
    for (int i = 1; i <= 4; i++) cin >> a[i][0];

    bt(0);

    cout << ans;
}
