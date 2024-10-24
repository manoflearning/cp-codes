#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int dy[] = {1, 0, -1, 0};
const int dx[] = {0, 1, 0, -1};
const int INF = 1e9 + 7;

int h, w, a[1010][1010];

void input() {
    cin >> h >> w;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            cin >> a[y][x];
        }
    }
}

inline int Hash(int y, int x) { return y * 1010 + x; }

struct UF {
    vector<ll> uf;
    void build() {
        uf.clear();
        uf.resize(1010 * 1010, -1);
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                if (y == 0 || y == h - 1 || x == 0 || x == w - 1) uf[Hash(y, x)] = -INF;
                else uf[Hash(y, x)] = -1;
            }
        }
    }
    int find(int x) {
        if (uf[x] < 0) return x;
        return uf[x] = find(uf[x]);
    }
    void merge(int u, int v) {
        int U = find(u), V = find(v);
        if (U == V) return;
        uf[U] += uf[V];
        uf[V] = U;
    }
} uf;

ll ans = 0;
map<int, vector<pii>> mp;
void solve() {
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            mp[a[y][x]].push_back({y, x});
        }
    }
    uf.build();
    for (auto &[_, coor] : mp) {
        for (auto &[y, x] : coor) {
            for (int d = 0; d < 4; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (ny < 0 || h <= ny || nx < 0 || w <= nx) continue;
                if (a[y][x] < a[ny][nx]) continue;
                uf.merge(Hash(y, x), Hash(ny, nx));
            }
        }
        for (auto &[y, x] : coor) {
            int ro = uf.find(Hash(y, x));
            if (INF <= -uf.uf[ro]) continue;
            ans = max(ans, -uf.uf[ro]);
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

    input();

    solve();

    cout << ans;
}
