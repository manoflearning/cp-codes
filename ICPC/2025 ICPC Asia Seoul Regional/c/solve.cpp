#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define fr first
#define sc second
#define all(x) (x).begin(), (x).end()

constexpr int N = 303;

constexpr int dy[] = {0, -1, 0, 1};
constexpr int dx[] = {-1, 0, 1, 0};

int n, s;
set<pii> e;

int sum[N - 1][N - 1];

int ans1 = 0;
pii ans2{-1, -1};

void add_edge(int u, int v) {
    if (u > v) swap(u, v);
    e.insert({u, v});
}
bool is_exist(int u, int v) {
    if (u > v) swap(u, v);
    return e.count({u, v});
}

void input() {
    cin >> n >> s;
    for (int i = 0; i < n * n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        add_edge(u, v);
    }
}

int _hash(int y, int x) { return y * n + x; }
bool is_l_open(int y, int x) { return !is_exist(_hash(y, x), _hash(y + 1, x)); }
bool is_u_open(int y, int x) { return !is_exist(_hash(y, x), _hash(y, x + 1)); }
bool is_r_open(int y, int x) { return !is_exist(_hash(y, x + 1), _hash(y + 1, x + 1)); }
bool is_d_open(int y, int x) { return !is_exist(_hash(y + 1, x), _hash(y + 1, x + 1)); }
pii get_hash(int y, int x, int d) {
    if (d == 0) return {_hash(y, x), _hash(y + 1, x)};
    if (d == 1) return {_hash(y, x), _hash(y, x + 1)};
    if (d == 2) return {_hash(y, x + 1), _hash(y + 1, x + 1)};
    if (d == 3) return {_hash(y + 1, x), _hash(y + 1, x + 1)};
}

void dfs(int y, int x, int pdir) {
    // cout << y << ' ' << x << ' ' << pdir << endl;
    sum[y][x] = 1;

    for (int d = 0; d < 4; d++) {
        if (d == pdir) continue;
        int ny = y + dy[d], nx = x + dx[d];
        
        if (d == 0 && !is_l_open(y, x)) continue;
        if (d == 1 && !is_u_open(y, x)) continue;
        if (d == 2 && !is_r_open(y, x)) continue;
        if (d == 3 && !is_d_open(y, x)) continue;

        dfs(ny, nx, d < 2 ? d + 2 : d - 2);
        sum[y][x] += sum[ny][nx];
    }

    if (sum[y][x] != s) return;

    pii res = get_hash(y, x, pdir);
    if (ans1 == 0 || res < ans2) {
        ans2 = res;
    }
    ans1++;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    input();

    for (int i = 0; i < n - 1; i++) {
        if (is_l_open(i, 0)) dfs(i, 0, 0);
        if (is_u_open(0, i)) dfs(0, i, 1);
        if (is_r_open(i, n - 2)) dfs(i, n - 2, 2);
        if (is_d_open(n - 2, i)) dfs(n - 2, i, 3);
    }

    cout << ans1 << '\n';
    cout << ans2.fr + 1 << ' ' << ans2.sc + 1;
}