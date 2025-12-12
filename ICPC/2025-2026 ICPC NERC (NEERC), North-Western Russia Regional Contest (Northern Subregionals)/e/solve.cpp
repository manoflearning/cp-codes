#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int X = 50;
constexpr int Y = 50;

int X_PAD, Y_PAD;

constexpr int dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
constexpr int dy[] = {1, 0, -1, 0, 1, -1, 1, -1};

int n;
int co[X][Y], mask[X][Y];
int cnt_b{}, cnt_w{};
vector<pii> ans;

void init() {
    cnt_b = cnt_w = 0;
    ans.clear();
}

void query(int x, int y) {
    cout << "? " << x + X_PAD << ' ' << y + Y_PAD << '\n';
    cout << flush;

    char c; cin >> c;
    co[x][y] = (c == 'B' ? 1 : 2);
    if (c == '0') exit(0);

    if (c == 'B') cnt_b++;
    else cnt_w++;
}

vector<pii> res;
bool vis[X][Y]{};

void dfs(int x, int y) {
    if (sz(ans) == n) return;

    vis[x][y] = 1;
    res.push_back({x, y});

    if (sz(res) == n) {
        ans = res;
        return;
    }

    for (int d = 0; d < 8; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx < 0 || X <= nx || ny < 0 || Y <= ny) continue;
        if (co[x][y] != co[nx][ny]) continue;
        if (vis[nx][ny]) continue;
        if (!mask[nx][ny]) continue;

        dfs(nx, ny);
    }

    // vis[x][y] = 0;
    // res.pop_back();
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    mt19937 rng((unsigned)chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist(-(int)9e8, (int)9e8);
    auto gen = bind(dist, rng);

    int mask_cnt = 0;
    mask[25][25] = 1;
    mask_cnt++;

    for (int len = 1; ; len++) {
        if (mask_cnt == 600) break;
        for (int len_y = 0; len_y <= len; len_y++) {
            int len_x = len - len_y;

            for (int d = 4; d < 8; d++) {
                if (mask_cnt == 600) break;
                int nx = 25 + len_x * dx[d];
                int ny = 25 + len_y * dy[d];

                if (mask[nx][ny]) continue;
                // assert(!mask[nx][ny]);
                mask[nx][ny] = 1;
                mask_cnt++;
            }
        }
    }

    // for (int i = 0; i < 50; i++) {
    //     for (int j = 0; j < 50; j++) {
    //         cout << mask[i][j];
    //     }
    //     cout << '\n';
    // }
    // cout << endl;

    int tc;
    cin >> tc >> n;

    while (tc--) {
        init();

        X_PAD = gen();
        Y_PAD = gen();

        for (int x = 0; x < X; x++) {
            for (int y = 0; y < Y; y++) {
                if (mask[x][y]) query(x, y);
            }
        }

        for (int x = 0; x < X; x++) {
            for (int y = 0; y < Y; y++) {
                if (!mask[x][y]) continue;

                if (sz(ans) != n) {
                    res.clear();
                    memset(vis, 0, sizeof(vis));
                    dfs(x, y);
                }
                if (sz(ans) != n) {
                    res.clear();
                    memset(vis, 0, sizeof(vis));
                    dfs(x, y);
                }
            }
        }

        // assert(!ans.empty());

        cout << "! " << (co[ans[0].fr][ans[0].sc] == 1 ? 'B' : 'W') << ' ';
        for (auto &[x, y] : ans) {
            cout << x + X_PAD << ' ' << y + Y_PAD << ' ';
        }
        cout << '\n';
        cout << flush;
    }
}
