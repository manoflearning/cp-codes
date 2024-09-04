#include <bits/stdc++.h>
using namespace std;

const int dy[] = { 0, 1, 0, -1 };
const int dx[] = { 1, 0, -1, 0 };

int n;
vector<vector<int>> a;
vector<vector<int>> dir;
struct Point { int y, x; };
vector<vector<Point>> adj;
vector<vector<int>> ind;

void input() {
    cin >> n;
    a.resize(n, vector<int>(n));
    dir.resize(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            string s; cin >> s;
            if (s.back() == 'R') dir[i][j] = 0;
            else if (s.back() == 'D') dir[i][j] = 1;
            else if (s.back() == 'L') dir[i][j] = 2;
            else if (s.back() == 'U') dir[i][j] = 3;
            s.pop_back();
            a[i][j] = stoi(s);
        }
    }
}

void build_graph() {
    adj.resize(n, vector<Point>(n));
    ind.resize(n, vector<int>(n));
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            int ny = y + a[y][x] * dy[dir[y][x]], nx = x + a[y][x] * dx[dir[y][x]];
            adj[y][x] = { ny, nx };
            ind[ny][nx]++;
        }
    }
}

int get_traversable_nodes_cnt(int y, int x) {
    int ret = 0;
    vector<vector<bool>> vis(n, vector<bool>(n));
    while (!vis[y][x]) {
        ret++;
        vis[y][x] = 1;
        
        int ny = y + a[y][x] * dy[dir[y][x]];
        int nx = x + a[y][x] * dx[dir[y][x]];
        y = ny, x = nx;
    }
    return ret;
}

void solve() {
    bool is_case_1 = 0;
    int ind0_cnt = 0;
    int ind0_y = -1, ind0_x = -1;
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            if (ind[y][x] == 0) {
                is_case_1 = 1; ind0_cnt++;
                if (ind0_y == -1) ind0_y = y, ind0_x = x;
            }
        }
    }

    // case 1: there exists (y, x) s.t. ind[y][x] == 0
    // case 1.1: there exists exactly one coordinate (y, x) s.t. ind[y][x] = 0
    // case 1.2: otherwise => "TOO SAFE"
    if (is_case_1) {
        if (ind0_cnt == 1 && get_traversable_nodes_cnt(ind0_y, ind0_x) == n * n) {
            cout << ind0_y + 1 << ' ' << ind0_x + 1;
        }
        else cout << "TOO SAFE";
    }
    // case 2: otherwise
    // case 2.1: there is exactly one component => "THIEF LOVE IT!"
    // case 2.2: otherwise => "TOO SAFE"
    else {
        if (get_traversable_nodes_cnt(0, 0) == n * n) cout << "THIEF LOVE IT!";
        else cout << "TOO SAFE";
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    build_graph();

    solve();
}