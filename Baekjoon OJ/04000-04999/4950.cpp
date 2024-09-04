#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()

const int dy[] = { 1, 0, -1, 0 };
const int dx[] = { 0, 1, 0, -1 };

int h, w, c;
vector<vector<int>> a;
vector<set<vector<vector<int>>>> st;

void dfs(int y, int x, vector<vector<bool>>& vis, vector<vector<int>>& now, const vector<vector<int>>& prv, int co) {
    now[y][x] = co;
    vis[y][x] = 1;
    for (int d = 0; d < 4; d++) {
        int ny = y + dy[d], nx = x + dx[d];
        if (ny < 0 || h <= ny || nx < 0 || w <= nx) continue;
        if (vis[ny][nx]) continue;
        if (prv[y][x] != prv[ny][nx]) continue;
        dfs(ny, nx, vis, now, prv, co);
    }
}

int count_co(int y, int x, vector<vector<bool>>& vis, const vector<vector<int>>& now, int co) {
    int ret = 1;
    vis[y][x] = 1;
    for (int d = 0; d < 4; d++) {
        int ny = y + dy[d], nx = x + dx[d];
        if (ny < 0 || h <= ny || nx < 0 || w <= nx) continue;
        if (vis[ny][nx]) continue;
        if (now[y][x] != now[ny][nx]) continue;
        ret += count_co(ny, nx, vis, now, co);
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

    while (1) {
        // initialize
        a.clear();
        st.clear();

        // input
        cin >> h >> w >> c;
        if (h == 0 && w == 0 && c == 0) break;

        a.resize(h, vector<int>(w));
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                cin >> a[i][j];
            }
        }

        // base case
        st.resize(6);
        st[0].insert(a);

        // inductive step
        for (int step = 1; step <= 5; step++) {
            for (auto& prv : st[step - 1]) {
                for (int co = 1; co <= 6; co++) {
                    // if (prv[0][0] == co) continue;
                    vector<vector<bool>> vis(h, vector<bool>(w));
                    vector<vector<int>> now = prv;

                    dfs(0, 0, vis, now, prv, co);

                    st[step].insert(now);
                }
            }
        }

        // get answer
        int ans = 0;
        for (auto& now : st[5]) {
            if (now[0][0] != c) continue;
            vector<vector<bool>> vis(h, vector<bool>(w));
            ans = max(ans, count_co(0, 0, vis, now, c));
        }

        cout << ans << '\n';
    }
}
