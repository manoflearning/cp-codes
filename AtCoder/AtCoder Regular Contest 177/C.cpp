// #pragma GCC optimize ("O3")
// #pragma GCC optimize ("Ofast")
// #pragma GCC optimize ("unroll-loops")
// #pragma GCC target ("avx2")

#include <bits/stdc++.h>
// #include <x86intrin.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

// struct UF {
//     vector<int> uf;
//     void init(int n) {
//         uf.clear();
//         uf.resize(n + 1, -1);
//     }
//     int find(int x) {
//         if (uf[x] < 0) return x;
//         return uf[x] = find(uf[x]);
//     }
//     void merge(int u, int v) {
//         int U = find(u), V = find(v);
//         if (U == V) return;
//         uf[U] += uf[V];
//         uf[V] = U;
//     }
// }ds;

int N;
string c[505];
// map<int, vector<pii>> R, B;
// struct Edge { ll w; int v; };
// vector<Edge> adj[252525];

void input() {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> c[i];
}

// inline int hash_yx(int y, int x) { return N * y + x; }

// void build_graph() {
//     // union find
//     ds.init(N * N);
//     for (int y = 0; y < N; y++) {
//         for (int x = 0; x < N; x++) {
//             for (int d = 0; d < 4; d++) {
//                 int ny = y + dy[d], nx = x + dx[d];
//                 if (ny < 0 || N <= ny || nx < 0 || N <= nx) continue;
//                 if (c[y][x] != c[ny][nx]) continue;

//                 ds.merge(hash_yx(y, x), hash_yx(ny, nx));
//             }
//         }
//     }

//     for (int y = 0; y < N; y++) {
//         for (int x = 0; x < N; x++) {
//             // greedily fuses the cells
//             // bool is_edge = 0;
//             // for (int d = 0; d < 4; d++) {
//             //     int ny = y + dy[d], nx = x + dx[d];
//             //     if (ny < 0 || N <= ny || nx < 0 || N <= nx) continue;
//             //     if (c[y][x] != c[ny][nx]) is_edge = 1;
//             // }

//             // if (!is_edge) continue;

//             if (c[y][x] == 'R') R[ds.find(hash_yx(y, x))].push_back({ y, x });
//             if (c[y][x] == 'B') B[ds.find(hash_yx(y, x))].push_back({ y, x });
//         }
//     }

//     // constructing graph takes O((N^2)^2) time

// }

struct Node {
    int w, y, x;
    bool operator<(const Node& rhs) const {
        return w > rhs.w;
    }
};

int dijkstra(int sy, int sx, int ey, int ex, char co) {
    vector<vector<int>> dist(N, vector<int>(N, INF));
    priority_queue<Node> pq;

    dist[sy][sx] = 0;
    pq.push({ dist[sy][sx], sy, sx });

    while (!pq.empty()) {
        auto [w, y, x] = pq.top();
        pq.pop();

        if (dist[y][x] < w) continue;

        for (int d = 0; d < 4; d++) {
            int ny = y + dy[d], nx = x + dx[d], nw = w;
            if (ny < 0 || N <= ny || nx < 0 || N <= nx) continue;
            if (c[ny][nx] != co) nw++;
            if (dist[ny][nx] <= nw) continue;
            dist[ny][nx] = nw;
            pq.push({ dist[ny][nx], ny, nx });
        }
    }

    return dist[ey][ex];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    cout << dijkstra(0, 0, N-1, N-1, 'R') + dijkstra(0, N-1, N-1, 0, 'B');
}

// * if we change all the cells to purple, then the conditions are satisfied (ans <= N*N)
// * the operation only makes the number of the sets smaller
// * shortest path?