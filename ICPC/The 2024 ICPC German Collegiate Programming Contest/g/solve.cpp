#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr char P[12] = {'F', 'I', 'L', 'N', 'P', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
constexpr int dy[] = {0, 1, 0, -1};
constexpr int dx[] = {1, 0, -1, 0};

struct Point { int x, y; };

const vector<vector<Point>> PE = {
    {{0, 0}, {0, 1}, {1, -1}, {1, 0}, {2, 0}},
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}},
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {3, 1}},
    {{0, 0}, {0, 1}, {1, 1}, {1, 2}, {1, 3}},
    {{0, 0}, {0, 1}, {1, 0}, {1, 1}, {2, 0}},
    {{0, 0}, {0, 1}, {0, 2}, {1, 1}, {2, 1}},
    {{0, 0}, {0, 2}, {1, 0}, {1, 1}, {1, 2}},
    {{0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}},
    {{0, 0}, {1, 0}, {1, 1}, {2, 1}, {2, 2}},
    {{0, 0}, {1, -1}, {1, 0}, {1, 1}, {2, 0}},
    {{0, 0}, {1, -2}, {1, -1}, {1, 0}, {1, 1}},
    {{0, 0}, {0, 1}, {1, 1}, {2, 1}, {2, 2}},
};

const vector<vector<vector<int>>> FXF = {
    {
        {0,0,7,7,7 },
        {10,0,0,3,7 },
        {10,0,5,3,7 },
        {10,10,5,3,3 },
        {10,5,5,5,3 },
    },
    {
        {0,0,2,2,2,2 },
        {10,0,0,4,4,2 },
        {10,0,4,4,4,7 },
        {10,10,3,3,3,7 },
        {10,3,3,7,7,7 },
    },
    {
        {0,0,2,2,2,2,7 },
        {10,0,0,6,6,2,7 },
        {10,0,5,6,7,7,7 },
        {10,10,5,6,6,4,4 },
        {10,5,5,5,4,4,4 },
    },
    {
        {0,0,7,7,7,2,2,3 },
        {10,0,0,3,7,2,3,3 },
        {10,0,5,3,7,2,3,7 },
        {10,10,5,3,3,2,3,7 },
        {10,5,5,5,3,7,7,7 },
    },
    {
        {0,0,7,7,7,2,2,2,2 },
        {10,0,0,3,7,3,3,3,2 },
        {10,0,5,3,7,6,6,3,3 },
        {10,10,5,3,3,6,4,4,4 },
        {10,5,5,5,3,6,6,4,4 },
    }   
};

// const vector<vector<int>> FUCK = {
//     {

//     },
//     {

//     },
//     {

//     },
//     {
//         {0,0,2,2 },
//         {10,0,0,2 },
//         {10,0,5,2 },
//         {10,10,5,2 },
//         {10,5,5,5 },
//     }
// };

// void draw() {
//     for (int i = 0; i < 12; i++) {
//         vector<vector<int>> a(10, vector<int>(10));
//         for (const auto [x, y] : PE[i]) a[x + 5][y + 5] = 1;
//         for (int x = 0; x < 10; x++) {
//             for (int y = 0; y < 10; y++) {
//                 cout << a[x][y] << ' ';
//             }
//             cout << '\n';
//         }
//         cout << '\n';
//     }
// }

void yes(const int h, const int w, const vector<vector<int>> &ans) {
    cout << "yes\n";
    for (int i = 0; i < h; i++) {
        // cout << "{";
        for (int j = 0; j < w; j++) {
            cout << P[ans[i][j]];
            // cout << ans[i][j] << ", "[j + 1 == w];
        }
        // cout << "},";
        cout << '\n';
    }
}
void no() { cout << "no\n"; }

vector<Point> togo;
vector<vector<int>> vis;
bool done = false;
int h, w;
void bt(int idx) {
    if (idx == sz(togo)) { done = 1; return; }
    const auto [x, y] = togo[idx];
    if (vis[x][y] != -1) { bt(idx + 1); return; }

    for (int p = 0; p < 12; p++) {
        const auto &pe = PE[p];

        // bool used = false;
        // for (int x = 0; x < h; x++) {
        //     for (int y = 5; y < w; y++) {
        //         if (vis[x][y] == p) used = true;
        //     }
        // }
        // if (used) continue;
        // if (P[p] == 'I') continue;

        for (int m = 0; m < 5; m++) {
            for (const int ro : {0, 1, 2, 3}) {
                for (const int fl : {-1, +1}) {
                    array<Point, 5> np{};
                    for (int i = 0; i < 5; i++) {
                        np[i].x = (pe[i].x - pe[m].x);
                        np[i].y = (pe[i].y - pe[m].y) * fl;

                        if (ro == 0) {
                            continue;
                        } else if (ro == 1) {
                            swap(np[i].x, np[i].y);
                            np[i].x *= -1;
                        } else if (ro == 2) {
                            swap(np[i].x, np[i].y);
                            np[i].y *= -1;
                        } else if (ro == 3) {
                            np[i].x *= -1, np[i].y *= -1;
                        }

                        np[i].x += x, np[i].y += y;
                    }

                    bool yes = true;
                    for (const auto &i : np) {
                        if (i.x < 0 || h <= i.x || i.y < 0 || w <= i.y) { yes = false; break; }
                        if (vis[i.x][i.y] != -1) { yes = false; break; }

                        bool res = true;
                        for (int d = 0; d < 4; d++) {
                            const int nx = i.x + dx[d], ny = i.y + dy[d];
                            if (nx < 0 || h <= nx || ny < 0 || w <= ny) continue;
                            if (vis[nx][ny] == p) { res = false; break; }
                        }
                        if (!res) { yes = false; break; }
                    }

                    if (!yes) continue;

                    for (const auto &i : np) vis[i.x][i.y] = p;
                    bt(idx + 1);
                    if (done) return;
                    for (const auto &i : np) vis[i.x][i.y] = -1;
                }
            }
        }
    }
}

template <bool PRINT>
void solve(int _h, int _w) {
    h = _h, w = _w;
    if (h * w % 5) { if (PRINT) no(); return; }

    bool swapped = false;
    if (h % 5) {
        swapped = true;
        swap(h, w);
    }

    vis.assign(h, vector<int>(w, -1));

    done = false;
    togo.clear();

    if (w >= 5) {
        for (int i = 0; i < h; i += 5) {
            for (int j = 0; j < w / 5 * 5; j += 5) {
                for (int x = 0; x < 5; x++) {
                    for (int y = 0; y < 5; y++) {
                        vis[x + i][y + j] = FXF[0][x][y];
                    }
                }
            }
        }
        const int base = w / 5 * 5 - 5;
        for (int x = 0; x < h; x++) {
            for (int y = base; y < w; y++) {
                vis[x][y] = FXF[w % 5][x % 5][y - base];
            }
        }
        done = true;
    } else {
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (vis[i][j] == -1) togo.push_back({i, j});
            }
        }
        bt(0);
    }

    if (PRINT) {
        if (swapped) {
            vector<vector<int>> tmp(w, vector<int>(h));
            for (int x = 0; x < h; x++) {
                for (int y = 0; y < w; y++) {
                    tmp[y][x] = vis[x][y];
                }
            }
            vis = tmp;
            swap(h, w);
        }

        if (done) yes(h, w, vis);
        else no();
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int h, w;
    cin >> h >> w;

    solve<true>(h, w);
}
