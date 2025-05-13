#include <bits/stdc++.h>
using namespace std;

const int N = 505;

const int dy[] = {0, 1, 0, -1};
const int dx[] = {1, 0, -1, 0};

int n;
int ans[N][N];

void init() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans[i][j] = -1;
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    memset(ans, -1, sizeof(ans));

    int tc; cin >> tc;
    while (tc--) {
        init();

        cin >> n;

        int y = (n - 1) / 2, x = (n - 1) / 2;
        int d = 3;

        int now = 0;
        while (1) {
            ans[y][x] = now++;
            if (now > n * n - 1) break;
            
            int nd = (d + 1) % 4;
            int ny = y + dy[nd], nx = x + dx[nd];
            if (ans[ny][nx] == -1) d = nd;
            y = y + dy[d], x = x + dx[d];
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << ans[i][j] << ' ';
            }
            cout << '\n';
        }
    }
}
