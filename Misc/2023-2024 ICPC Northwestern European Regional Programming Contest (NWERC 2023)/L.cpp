#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int dy[] = {1, 0, -1, 0};
const int dx[] = {0, 1, 0, -1};

int a[101][101];

string query(int y, int x) {
    cout << y + 1 << ' ' << x + 1 << '\n';
    cout << flush;
    string ret; cin >> ret;
    return ret;
}

int main() {
    // #ifndef ONLINE_JUDGE
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // #endif

    // cin.tie(NULL); cout.tie(NULL);
    // ios_base::sync_with_stdio(false);

    int n, k;
    cin >> n >> k;

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            if (x % 5 == 2 * y % 5) {
                string res = query(y, x);
                a[y][x] = 1;

                if (res == "hit" || res == "sunk") {
                    for (int d = 0; d < 4; d++) {
                        for (int len = 1; len <= 4; len++) {
                            int ny = y + dy[d] * len, nx = x + dx[d] * len;
                            if (ny < 0 || n <= ny || nx < 0 || n <= nx) continue;
                            string res = query(ny, nx);
                        }
                    }
                }
            }
        }
    }

    // for (int y = 0; y < n; y++) {
    //     for (int x = 0; x < n; x++) {
    //         cout << a[y][x] << ' ';
    //     }
    //     cout << '\n';
    // }
}
