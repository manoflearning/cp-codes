#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int dy[] = { 1, 0 };
const int dx[] = { 0, 1 };

int n, a[1010][1010];
int a2[1010][1010], a5[1010][1010];

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int x; cin >> x;
            a[i][j] = x;
            if (x == 0) continue;
            while (x % 2 == 0) a2[i][j]++, x /= 2;
            while (x % 5 == 0) a5[i][j]++, x /= 5;
        }
    }
}

// struct State {
//     int y, x, w5;
//     bool operator<(const State& rhs) const {
//         if (w5 ^ rhs.w5) return w5 > rhs.w5;
//         if (y ^ rhs.y) return y < rhs.y;
//         return x < rhs.x;
//     }
// };

inline ll Hash(int y, int x, int w5) {
    return 1010ll * 1010 * w5 + 1010 * y + x;
}
inline int get_y(ll num) { return num % (1010 * 1010) / 1010; }
inline int get_x(ll num) { return num % 1010; }
inline int get_w5(ll num) { return num / (1010 * 1010); }

int dijkstra() {
    int ret = 1e9;

    unordered_map<ll, int> dist;
    priority_queue<pair<int, ll>> pq;

    dist[Hash(1, 1, a5[1][1])] = a2[1][1];
    pq.push({ a2[1][1], Hash(1, 1, a5[1][1]) });

    while (!pq.empty()) {
        auto [w2, v] = pq.top();
        pq.pop();
        
        if (dist[v] < w2) continue;
        int y = get_y(v), x = get_x(v), w5 = get_w5(v);
        if (ret <= min(w2, w5)) continue;
        if (y == n && x == n) {
            ret = min(ret, min(w2, w5));
            continue;
        }

        for (int d = 0; d < 2; d++) {
            int ny = y + dy[d], nx = x + dx[d];
            if (n < ny || n < nx) continue;
            if (a[ny][nx] == 0) continue;
            int nw5 = w5 + a5[ny][nx], nw2 = w2 + a2[ny][nx];
            ll u = Hash(ny, nx, nw5);
            if (dist.count(u) && dist[u] <= nw2) continue;
            dist[u] = nw2;
            pq.push({ dist[u], u });
        }
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

    input();
    
    // cout << dijkstra();
}

// number of 5 <= 8 * (2n-1)