#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAX = 999 * 1000 + 999 + 100;

inline int Hash(int y, int x) { return (y - 1) * 1000 + (x - 1); }

struct wv {
    ll w; int v;
    bool operator<(const wv& rhs) const {
        return w > rhs.w;
    }
};

int n, sy, sx, ey, ex;
vector<string> a;
vector<wv> adj[MAX];

void input() {
    cin >> n;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        a[i].resize(n + 1);
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            if (a[i][j] == 'P') {
                sy = i, sx = j;
            }
            if (a[i][j] == 'K') {
                ey = i, ex = j;
            }
        }
    }
}

const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

void buildQRBedge(int y, int x, char c) {
    int lb = 0, rb = 8;
    if (c == 'R') rb = 4;
    if (c == 'B') lb = 4;

    for (int i = lb; i < rb; i++) {
        int ny = y, nx = x;
        while (1) {
            ny += dy[i], nx += dx[i];
            if (ny < 1 || n < ny || nx < 1 || n < nx) break;
            if (a[ny][nx] == '0' || a[ny][nx] == 'P') continue;
            
            int w = max(abs(y - ny), abs(x - nx));
            adj[Hash(y, x)].push_back({ w, Hash(ny, nx )});
            break;
        }
    }
}

void buildNedge(int y, int x) {
    const int dyn[] = { 1, 1, 2, 2, -1, -1, -2, -2 };
    const int dxn[] = { 2, -2, 1, -1, 2, -2, 1, -1 };

    for (int i = 0; i < 8; i++) {
        int ny = y + dyn[i], nx = x + dxn[i];
        if (ny < 1 || n < ny || nx < 1 || n < nx) continue;
        if (a[ny][nx] == '0' || a[ny][nx] == 'P') continue;
        adj[Hash(y, x)].push_back({ 2, Hash(ny, nx) });
    }
}

void buildPedge(int y, int x) {
    for (int i = 0; i < 8; i++) {
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 1 || n < ny || nx < 1 || n < nx) continue;
        if (a[ny][nx] == '0' || a[ny][nx] == 'P') continue;
        adj[Hash(y, x)].push_back({ 1, Hash(ny, nx) });
    }
}

void buildGraph() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] == '0') continue;

            if (a[i][j] == 'Q') buildQRBedge(i, j, a[i][j]);
            else if (a[i][j] == 'R') buildQRBedge(i, j, a[i][j]);
            else if (a[i][j] == 'B') buildQRBedge(i, j, a[i][j]);
            else if (a[i][j] == 'N') buildNedge(i, j);
            else if (a[i][j] == 'P') buildPedge(i, j);
        }
    }
}

ll dijkstra(int st, int en) {
    vector<ll> dist(MAX, 1e18);
    priority_queue<wv> pq;
    dist[st] = 0;
    pq.push({ 0, st });

    while (!pq.empty()) {
        int v = pq.top().v;
        ll w = pq.top().w;
        pq.pop();
        if (w > dist[v]) continue;
        if (v == en) return w;
        for (auto& i : adj[v]) {
            if (dist[i.v] > w + i.w) {
                dist[i.v] = w + i.w;
                pq.push({ w + i.w, i.v });
            }
        }
    }
    return -1;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    buildGraph();

    cout << dijkstra(Hash(sy, sx), Hash(ey, ex));

    return 0;
}