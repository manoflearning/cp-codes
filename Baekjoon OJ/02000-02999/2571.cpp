#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n;
int a[111][111], psum[111][111];

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int sx, sy;
        cin >> sx >> sy;
        sx++, sy++;
        for (int x = sx; x < sx + 10; x++) {
            for (int y = sy; y < sy + 10; y++) {
                a[x][y] = 1;
            }
        }
    }

    /*psum[0][0] = a[0][0];

    for (int i = 1; i <= 101; i++) {
        psum[i][0] = a[i][0] + psum[i - 1][0];
        psum[0][i] = a[0][i] + psum[0][i - 1];
    }*/

    for (int x = 1; x <= 110; x++) {
        for (int y = 1; y <= 110; y++) {
            psum[x][y] = a[x][y];
            psum[x][y] += psum[x - 1][y];
            psum[x][y] += psum[x][y - 1];
            psum[x][y] -= psum[x - 1][y - 1];
        }
    }

    int ans = 0;
    for (int sx = 1; sx <= 110; sx++) {
        for (int ex = sx; ex <= 110; ex++) {
            for (int sy = 1; sy <= 110; sy++) {
                for (int ey = sy; ey <= 110; ey++) {
                    int res1 = (ex - sx + 1) * (ey - sy + 1);
                    int res2 = psum[ex][ey] - psum[ex][sy - 1] - psum[sx - 1][ey] + psum[sx - 1][sy - 1];
                    if (res1 == res2) ans = max(ans, res1);
                    else break;
                }
            }
        }
    }

    cout << ans;

    return 0;
}