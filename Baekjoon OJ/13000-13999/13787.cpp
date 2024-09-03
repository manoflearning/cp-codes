#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(a) (int)(a).size()

const int dy[] = { -1, 0, 1, 0 };
const int dx[] = { 0, 1, 0, -1 };
const char d[] = { 'N', 'E', 'S', 'W' };

int h, w;
ll l;
int sty, stx, dir;
int cycle_st;
vector<string> a;

bool vis[121][121][4];
vector<tuple<int, int, int>> ans;

int get_dir(char c) {
    if (c == 'N') return 0;
    else if (c == 'E') return 1;
    else if (c == 'S') return 2;
    else if (c == 'W') return 3;
    else assert(0);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    while (1) {
        cin >> h >> w >> l;
        if (h == 0 && w == 0 && l == 0) break;

        a.resize(h);
        for (auto& i : a) cin >> i;

        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                if (a[y][x] != '#' && a[y][x] != '.') {
                    sty = y, stx = x;
                    dir = get_dir(a[y][x]);
                    y = h, x = w;
                    break;
                }
            }
        }

        memset(vis, 0, sizeof(vis));
        ans.clear();

        vis[sty][stx][dir] = 1;
        ans.push_back({ sty, stx, dir });

        int y = sty, x = stx;
        while (1) {
            int ny = y + dy[dir], nx = x + dx[dir];

            bool is_valid = 1;
            if (ny < 0 || h <= ny || nx < 0 || w <= nx) is_valid = 0;
            else if (a[ny][nx] == '#') is_valid = 0;

            if (is_valid) {
                if (vis[ny][nx][dir]) {
                    for (int i = 0; i < sz(ans); i++) {
                        if (get<0>(ans[i]) == ny && get<1>(ans[i]) == nx && get<2>(ans[i]) == dir) {
                            cycle_st = i;
                            break;
                        }
                    }
                    break;
                }
                else {
                    ans.push_back({ ny, nx, dir });
                    vis[ny][nx][dir] = 1;
                    y = ny, x = nx;
                }
            }
            else dir = (dir + 1) % 4;
        }

        if (l < sz(ans)) {
            cout << get<0>(ans[l]) + 1 << ' ';
            cout << get<1>(ans[l]) + 1 << ' ';
            cout << d[get<2>(ans[l])] << '\n';
        }
        else {
            l -= cycle_st;
            vector<tuple<int, int, int>> tmp;
            for (int i = cycle_st; i < sz(ans); i++) {
                tmp.push_back(ans[i]);
            }

            cout << get<0>(tmp[l % sz(tmp)]) + 1 << ' ';
            cout << get<1>(tmp[l % sz(tmp)]) + 1 << ' ';
            cout << d[get<2>(tmp[l % sz(tmp)])] << '\n';
        }
    }
}