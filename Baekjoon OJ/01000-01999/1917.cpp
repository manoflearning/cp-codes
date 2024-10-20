#include <bits/stdc++.h>
using namespace std;

const int dy[] = { -1, 0, 1, 0 };
const int dx[] = { 0, 1, 0, -1 };

int a[6][6], vi[6][6], cnt[6], prv[6][6];
vector<vector<int>> nxt = {
    { 4, 2, 1, 3 },
    { 0, 2, 5, 3 },
    { 4, 5, 1, 0 },
    { 4, 0, 1, 5 },
    { 5, 2, 0, 3 },
    { 4, 3, 1, 2 }
};

int dfs(int y, int x, int label) {
    cnt[label]++;
    vi[y][x] = 1;
    prv[y][x] = label;
    if (cnt[label] > 1) return 0;

    int add = 0;
    for (int d = 0; d < 4; d++) {
        int ny = y + dy[d], nx = x + dx[d];
        if (ny < 0 || 6 <= ny || nx < 0 || 6 <= nx) continue;
        if (!a[ny][nx] || !vi[ny][nx]) continue;

        for (int i = 0; i < 4; i++) {
            if (nxt[label][(d + i) % 4] == prv[ny][nx]) { add = i; break; }
        }
    }

    int ret = 1;
    for (int d = 0; d < 4; d++) {
        int ny = y + dy[d], nx = x + dx[d];
        if (ny < 0 || 6 <= ny || nx < 0 || 6 <= nx) continue;
        if (!a[ny][nx] || vi[ny][nx]) continue;
        ret &= dfs(ny, nx, nxt[label][(d + add) % 4]);
    }

    return ret;
}

int main() {
    int tc = 3;
    for (int tt = 0; tt < tc; tt++) {
        // initialize
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++)
                vi[i][j] = prv[i][j] = 0;
            cnt[i] = 0;
        }

        // input
        for (int i = 0; i < 6; i++) 
            for (int j = 0; j < 6; j++) cin >> a[i][j];
        
        // solve
        int ans = -1;
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                if (a[i][j]) {
                    ans = dfs(i, j, 0);
                    i = j = 6;
                    break;
                }
            }
        }

        cout << (ans ? "yes" : "no") << '\n';
    }
}