#include <bits/stdc++.h>
using namespace std;

const int dx[] = { 1, 0 };
const int dy[] = { 0, 1 };
const int MXH = 1010101;

int n, m, q;
int h[505][505];
struct Query {
    int st, en, l, r;
};
vector<Query> qu;
vector<pair<int, int>> adj[MXH];

inline int Hash(int x, int y) { return x * m + y; }

void input() {
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> h[i][j];
        }
    }
    qu.resize(q);
    for (int i = 0; i < q; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1--, y1--, x2--, y2--;
        qu[i].st = Hash(x1, y1);
        qu[i].en = Hash(x2, y2);
        qu[i].l = max(h[x1][y1], h[x2][y2]);
        qu[i].r = MXH - 1;
    }
}

vector<int> idx[MXH];

vector<int> uf(252525, -1);
int find(int x) {
    if (uf[x] < 0) return x;
    return uf[x] = find(uf[x]);
}
void merge(int u, int v) {
    int U = find(u), V = find(v);
    if (U == V) return;
    uf[U] = V;
}

void pbsInit() {
    for (int i = 0; i < MXH; i++) idx[i].clear();
    for (auto& i : uf) i = -1;

    for (int i = 0; i < q; i++) {
        if (qu[i].l == qu[i].r) continue;
        int mid = (qu[i].l + qu[i].r) >> 1;
        assert(1 <= mid && mid < MXH);
        idx[mid].push_back(i);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            for (int i = 0; i < 2; i++) {
                int nx = x + dx[i], ny = y + dy[i];
                if (n <= nx || m <= ny) continue;
                assert(max(h[x][y], h[nx][ny]) < MXH);
                adj[max(h[x][y], h[nx][ny])].push_back({ Hash(x, y), Hash(nx, ny) });
            }
        }
    }

    for (int t = 0; t < 20; t++) {
        pbsInit();

        for (int mid = 1; mid < MXH; mid++) {
            for (auto& i : adj[mid]) {
                merge(i.first, i.second);
            }

            for (auto& i : idx[mid]) {
                assert(0 <= i && i < q);
                int st = qu[i].st, en = qu[i].en;
                if (find(st) == find(en)) qu[i].r = mid;
                else qu[i].l = mid + 1;
            }
        }
    }

    for (int i = 0; i < q; i++)
        cout << qu[i].l << '\n';
}