#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()

const int dy[] = {0, 1};
const int dx[] = {1, 0};

int n, m;
int a[505][505], b[505][505];

inline int Hash(int y, int x) { return y * 505 + x; }

struct UF {
    vector<int> par, siz;
    void build(int k) {
        par.resize(k + 1, -1);
        siz.resize(k + 1);
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < m; x++) {
                if (b[y][x]) siz[Hash(y, x)] = 1;
            }
        }
    }
    int find(int x) {
        if (par[x] < 0) return x;
        return par[x] = find(par[x]);
    }
    void merge(int u, int v) {
        int U = find(u), V = find(v);
        if (U == V) return;
        par[U] = V;
        siz[V] += siz[U];
    }
} uf;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }

    int tot = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> b[i][j];
            if (b[i][j]) tot++;
        }
    }

    uf.build(505 * 505 + 505);

    vector<tuple<int, int, int>> e;
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            for (int d = 0; d < 2; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (n <= ny || m <= nx) continue;
                e.push_back({
                    abs(a[ny][nx] - a[y][x]),
                    Hash(y, x),
                    Hash(ny, nx)
                });
            }
        }
    }

    sort(all(e));

    if (tot == 1) {
        cout << 0;
        exit(0);
    }

    for (auto [w, u, v] : e) {
        uf.merge(u, v);
        if (uf.siz[uf.find(u)] == tot) {
            cout << w;
            exit(0);
        }
    }
}
