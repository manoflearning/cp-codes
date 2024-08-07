#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int N, L;
int a[22][22];
ll dp[22][22][22][22][22];

void input() {
    cin >> N >> L;
    for (int y = 1; y <= N; y++) {
        for (int x = 1; x <= N; x++) {
            cin >> a[y][x];
        }
    }
}

void cal(int y1, int x1, int y2, int x2, int k) {
    for (int d1 = 0; d1 < 8; d1++) {
        int ny1 = y1 + dy[d1], nx1 = x1 + dx[d1];
        if (ny1 < 1 || N < ny1 || nx1 < 1 || N < nx1) continue;
        for (int d2 = 0; d2 < 8; d2++) {
            int ny2 = y2 + dy[d2], nx2 = x2 + dx[d2];
            if (ny2 < 1 || N < ny2 || nx2 < 1 || N < nx2) continue;
            if (a[ny1][nx1] ^ a[ny2][nx2]) continue;
            dp[y1][x1][y2][x2][k] += dp[ny1][nx1][ny2][nx2][k - 2];
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    for (int y = 1; y <= N; y++) {
        for (int x = 1; x <= N; x++) {
            dp[y][x][y][x][1] = 1;
            for (int d = 0; d < 8; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (ny < 1 || N < ny || nx < 1 || N < nx) continue;
                if (a[y][x] ^ a[ny][nx]) continue;
                dp[y][x][ny][nx][2]++;
            }
        }
    }

    for (int k = 3; k <= L; k++) {
        for (int y1 = 1; y1 <= N; y1++) {
            for (int x1 = 1; x1 <= N; x1++) {
                for (int y2 = 1; y2 <= N; y2++) {
                    for (int x2 = 1; x2 <= N; x2++) {
                        if (a[y1][x1] ^ a[y2][x2]) continue;

                        cal(y1, x1, y2, x2, k);
                    }
                }
            }
        }
    }

    ll ans = 0;
    for (int y1 = 1; y1 <= N; y1++) {
        for (int x1 = 1; x1 <= N; x1++) {
            for (int y2 = 1; y2 <= N; y2++) {
                for (int x2 = 1; x2 <= N; x2++) {
                    if (a[y1][x1] ^ a[y2][x2]) continue;
                    ans += dp[y1][x1][y2][x2][L];
                }
            }
        }
    }

    cout << ans;
}