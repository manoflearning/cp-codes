#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second

const int dy[] = {1, 0, -1, 0};
const int dx[] = {0, 1, 0, -1};

int n, m, mxd;
vector<string> a;
int dist[33][33][33][33];

void input() {
    cin >> n >> m >> mxd;
    a.resize(n);
    for (auto &i : a) cin >> i;
}

void get_dist(int sty, int stx) {
    queue<pii> qu;
    qu.push({sty, stx});
    dist[sty][stx][sty][stx] = 0;
    while (!qu.empty()) {
        auto [y, x] = qu.front();
        qu.pop();

        if (a[y][x] != '.' && (y != sty || x != stx)) continue;

        for (int d = 0; d < 4; d++) {
            int ny = y + dy[d], nx = x + dx[d];
            if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;
            if (dist[sty][stx][ny][nx] != -1) continue;
            if (a[ny][nx] == '#') continue;
            dist[sty][stx][ny][nx] = 1 + dist[sty][stx][y][x];
            qu.push({ny, nx});
        }
    }
}

const int MAXV = 1818;
const int INF = 1e9 + 7;

ll c[MAXV][MAXV], f[MAXV][MAXV];
vector<int> adj[MAXV];
int prv[MAXV];
int st = MAXV - 2, en = MAXV - 1;

inline int Hash(int y, int x, int is_in) {
    return 2 * (y * 30 + x) + is_in;
}

void add_edge(int u, int v, int cap) {
    c[u][v] += cap;
    adj[u].push_back(v);
    // add reverse edge
    adj[v].push_back(u);
}
void build_graph() {
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            if (a[y][x] == 'S') {
                add_edge(st, Hash(y, x, 1), 1);
            }
            if (a[y][x] == 'P') {
                add_edge(Hash(y, x, 0), en, 1);
            }
            if (a[y][x] == 'H' || a[y][x] == 'S' || a[y][x] == 'P') {
                add_edge(Hash(y, x, 1), Hash(y, x, 0), 1);
            }
        }
    }

    for (int sy = 0; sy < n; sy++) {
        for (int sx = 0; sx < m; sx++) {
            for (int ey = 0; ey < n; ey++) {
                for (int ex = 0; ex < m; ex++) {
                    if (a[sy][sx] == 'S' && a[ey][ex] == 'H' && dist[sy][sx][ey][ex] != -1 && dist[sy][sx][ey][ex] <= mxd) {
                        add_edge(Hash(sy, sx, 0), Hash(ey, ex, 1), 1);
                    }
                    if (a[sy][sx] == 'H' && a[ey][ex] == 'P' && dist[sy][sx][ey][ex] != -1 && dist[sy][sx][ey][ex] <= mxd) {
                        add_edge(Hash(sy, sx, 0), Hash(ey, ex, 1), 1);
                    }
                }
            }
        }
    }
}

void bfs(int st, int en) {
  memset(prv, -1, sizeof(prv));
  queue<int> q;
  q.push(st);
  prv[st] = 0;
  while (!q.empty() && prv[en] == -1) {
    int now = q.front();
    q.pop();
    for (int next : adj[now]) {
      if (prv[next] == -1 && c[now][next] - f[now][next] > 0) {
        q.push(next);
        prv[next] = now;
      }
    }
  }
}
ll flow(int st, int en) {
  ll block = INF;
  for (int i = en; i != st; i = prv[i]) {
    block = min(block, c[prv[i]][i] - f[prv[i]][i]);
  }
  for (int i = en; i != st; i = prv[i]) {
    f[prv[i]][i] += block;
    f[i][prv[i]] -= block;
  }
  return block;
}
ll maxFlow(int st, int en) {
  ll ret = 0;
  while (1) {
    bfs(st, en);
    if (prv[en] == -1) break;
    ret += flow(st, en);
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

    memset(dist, -1, sizeof(dist));
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            if (a[y][x] == '#' || a[y][x] == '.') continue;
            get_dist(y, x);
        }
    }

    build_graph();

    ll total = maxFlow(st, en);
    cout << total << '\n';
}
