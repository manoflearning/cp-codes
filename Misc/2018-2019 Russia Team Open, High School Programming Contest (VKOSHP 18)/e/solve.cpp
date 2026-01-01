#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()

constexpr int dy[] = {-1, 1, 0, 0};
constexpr int dx[] = {0, 0, -1, 1};

struct point { int x, y; };

int k;
bool a[8][8], vis[8][8];
vector<pair<point, point>> ans;

void input() {
    cin >> k;
    for (int i = 0; i < k; i++) {
        string s; cin >> s;
        int x = s[0] - 'a', y = s[1] - '1';
        a[y][x] = vis[y][x] = 1;
    }
}

bool get_(const point &p) {
    return vis[p.y][p.x];
}
void set_(const point &p, bool v) {
    vis[p.y][p.x] = v;
}

point find_k(int tx, int ty) {
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (y < ty || (y == ty && x <= tx)) continue;
            if (get_({x, y})) return point{x, y};
        }
    }
    assert(0);
}

void mv(const point &u, const point &v) {
    assert(get_(u) == 1);
    assert(get_(v) == 0);
    ans.push_back({u, v});
    set_(u, 0);
    set_(v, 1);

    // DEBUG
    // for (int y = 0; y < 8; y++) {
    //     for (int x = 0; x < 8; x++) {
    //         cout << vis[y][x] << ' ';
    //     }
    //     cout << '\n';
    // }
    // cout << '\n';
}

void move(point p, int dir) {
    vector<point> path;

    if (dir == 0) {
        if (2 <= p.y) {
            if (2 <= p.x) {
                path.push_back({p.x - 1, p.y - 2});
                path.push_back({p.x - 2, p.y});
                path.push_back({p.x, p.y - 1});
            } else {
                path.push_back({p.x + 1, p.y - 2});
                path.push_back({p.x + 2, p.y});
                path.push_back({p.x, p.y - 1});
            }
        } else {
            if (2 <= p.x) {
                path.push_back({p.x - 1, p.y + 2});
                path.push_back({p.x - 2, p.y});
                path.push_back({p.x, p.y - 1});
            } else {
                path.push_back({p.x + 1, p.y + 2});
                path.push_back({p.x + 2, p.y});
                path.push_back({p.x, p.y - 1});
            }
        }
    } else if (dir == 2) {
        if (2 <= p.x) {
            if (2 <= p.y) {
                path.push_back({p.x - 2, p.y - 1});
                path.push_back({p.x, p.y - 2});
                path.push_back({p.x - 1, p.y});
            } else {
                path.push_back({p.x - 2, p.y + 1});
                path.push_back({p.x, p.y + 2});
                path.push_back({p.x - 1, p.y});
            }
        } else {
            if (2 <= p.y) {
                path.push_back({p.x + 2, p.y - 1});
                path.push_back({p.x, p.y - 2});
                path.push_back({p.x - 1, p.y});
            } else {
                path.push_back({p.x + 2, p.y + 1});
                path.push_back({p.x, p.y + 2});
                path.push_back({p.x - 1, p.y});
            }
        }
    } else if (dir == 3) {
        if (p.x + 2 < 8) {
            if (2 <= p.y) {
                path.push_back({p.x + 2, p.y - 1});
                path.push_back({p.x, p.y - 2});
                path.push_back({p.x + 1, p.y});
            } else {
                path.push_back({p.x + 2, p.y + 1});
                path.push_back({p.x, p.y + 2});
                path.push_back({p.x + 1, p.y});
            }
        } else {
            if (2 <= p.y) {
                path.push_back({p.x - 2, p.y - 1});
                path.push_back({p.x, p.y - 2});
                path.push_back({p.x + 1, p.y});
            } else {
                path.push_back({p.x - 2, p.y + 1});
                path.push_back({p.x, p.y + 2});
                path.push_back({p.x + 1, p.y});
            }
        }
    } else {
        assert(0);
    }

    if (get_(path[2])) {
        return;
    } else if (get_(path[1])) {
        mv(path[1], path[2]);

        if (get_(path[0])) {
            mv(path[0], path[1]);
            mv(p, path[0]);
        } else {
            mv(p, path[0]);
            mv(path[0], path[1]);
        }
    } else if (get_(path[0])) {
        mv(path[0], path[1]);
        mv(path[1], path[2]);

        mv(p, path[0]);
    } else {
        mv(p, path[0]);
        mv(path[0], path[1]);
        mv(path[1], path[2]);
    }
}

void solve() {
    // DEBUG
    // for (int y = 0; y < 8; y++) {
    //     for (int x = 0; x < 8; x++) {
    //         cout << vis[y][x] << ' ';
    //     }
    //     cout << '\n';
    // }
    // cout << '\n';

    int rem = k;
    for (int ty = 0; ty < 8; ty++) {
        for (int tx = 0; tx < 8; tx++) {    
            if (rem == 0) break;

            rem--;
            if (get_({tx, ty})) continue;
            // cout << tx << ' ' << ty << endl;
            auto p = find_k(tx, ty);

            assert(!(p.y < ty));
            
            while (tx < p.x) move(p, 2), p.x--;
            while (p.x < tx) move(p, 3), p.x++;
            // cout << "x move done\n\n";
            while (ty < p.y) move(p, 0), p.y--;
            // cout << "y move done\n\n";

            // cout << "done\n\n";
            assert(get_({tx, ty}));
        }
    }
}

void verify() {
    for (auto &[p1, p2] : ans) {
        assert(a[p1.y][p1.x] == 1);
        assert(a[p2.y][p2.x] == 0);
        a[p1.y][p1.x] = 0;
        a[p2.y][p2.x] = 1;
    }
    int rem = k;
    for (int ty = 0; ty < 8; ty++) {
        for (int tx = 0; tx < 8; tx++) {    
            assert(a[ty][tx] == (rem >= 1));
            rem--;
        }
    }
    // for (int ty = 0; ty < 8; ty++) {
    //     for (int tx = 0; tx < 8; tx++) {    
    //         // assert(a[tx][ty] == (rem >= 1));
    //         // rem--;
    //         cout << get_({tx, ty}) << ' ';
    //     }
    //     cout << '\n';
    // }
}

void print() {
    cout << sz(ans) << '\n';
    for (auto &[p1, p2] : ans) {
        cout << (char)(p1.x + 'a') << (char)(p1.y + '1') << '-' << (char)(p2.x + 'a') << (char)(p2.y + '1') << '\n';
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    input();

    solve();

    verify();
    
    print();
}
