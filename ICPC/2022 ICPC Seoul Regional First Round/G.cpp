#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long

int a, b, c;
int dp[101][101][101][30];

void init() {
    for (int i = 0; i < 101; i++) {
        for (int j = 0; j < 101; j++) {
            for (int k = 0; k < 101; k++) {
                for (int p = 0; p < 30; p++) {
                    dp[i][j][k][p] = -1;
                }
            }
        }
    }
}

int f(int x, int y, int z, int cnt) {
    int& ret = dp[x][y][z][cnt];
    if (x == 0 && y == 0 && z == 0) return ret = 0;

    if (cnt & 1) {
        ret = 0;
        if (x > 0) ret = max(ret, min(x, cnt) + f(max(0, x - cnt), y, z, cnt + 1));
        if (y > 0) ret = max(ret, min(y, cnt) + f(x, max(0, y - cnt), z, cnt + 1));
        if (z > 0) ret = max(ret, min(z, cnt) + f(x, y, max(0, z - cnt), cnt + 1));
    }
    else {
        ret = 1e9;
        if (x > 0) ret = min(ret, f(max(0, x - cnt), y, z, cnt + 1));
        if (y > 0) ret = min(ret, f(x, max(0, y - cnt), z, cnt + 1));
        if (z > 0) ret = min(ret, f(x, y, max(0, z - cnt), cnt + 1));
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

    cin >> a >> b >> c;
    
    int F = f(a, b, c, 1), S = (a + b + c) - F;
    if (F > S) cout << 'F';
    if (F < S) cout << 'S';
    if (F == S) cout << 'D';

    return 0;
}