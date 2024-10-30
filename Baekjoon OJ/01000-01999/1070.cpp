#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const int INF = 1e9 + 7;
const int MAXV = 5050;

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};

struct edge {
  int v;
  ll c, f;
  edge *dual; // pointer to reverse edge
  edge() : edge(-1, 0) {}
  edge(int v1, ll c1) : v(v1), c(c1), f(0), dual(nullptr) {}
  ll residual() {
    return c - f;
  }
  void addFlow(int f1) {
    f += f1;
    dual->f -= f1;
  }
};

int st = 0, en = 5049;
vector<edge *> adj[MAXV + 5];
int prv[MAXV + 5];
edge *path[MAXV + 5];

inline int Hash(int y, int x, int is_out) { return 2 * (y * 50 + x) + is_out; };

int n, m;
string a[55];
ll cost[26];

void input() {
    cin >> n >> m;
    int sty = -1, stx = -1;
    for (int y = 0; y < n; y++) {
        cin >> a[y];
        for (int x = 0; x < m; x++) {
            if (a[y][x] == '*') sty = y, stx = x;
        }
    }
    for (int i = 0; i < 26; i++) cin >> cost[i];
    st = Hash(sty, stx, 1);
}
void add_edge(int n1, int n2, int cap) {
    edge *e1 = new edge(n2, cap), *e2 = new edge(n1, 0);
    e1->dual = e2, e2->dual = e1;
    adj[n1].push_back(e1);
    adj[n2].push_back(e2);
}
void graph_modeling() {
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < m; x++) {
            if (a[y][x] == '-') continue;

            if (a[y][x] != '*') {
                int w = cost[a[y][x] - 'A'];
                // adj[Hash(y, x, 0)].push_back(Hash(y, x, 1));
                // adj[Hash(y, x, 1)].push_back(Hash(y, x, 0));
                // c[Hash(y, x, 0)][Hash(y, x, 1)] = (int)1e7 + w;
                add_edge(Hash(y, x, 0), Hash(y, x, 1), (int)1e7 + w);
            }

            for (int d = 0; d < 4; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (ny < 0 || n <= ny || nx < 0 || m <= nx) continue;
                if (a[ny][nx] == '-') continue;
                // adj[Hash(y, x, 1)].push_back(Hash(ny, nx, 0));
                // adj[Hash(ny, nx, 0)].push_back(Hash(y, x, 1));
                // c[Hash(y, x, 1)][Hash(ny, nx, 0)] = INF;
                add_edge(Hash(y, x, 1), Hash(ny, nx, 0), INF);
            }

            if (y == 0 || y == n - 1 || x == 0 || x == m - 1) {
                // adj[Hash(y, x, 1)].push_back(en);
                // adj[en].push_back(Hash(y, x, 1));
                // c[Hash(y, x, 1)][en] = INF;
                add_edge(Hash(y, x, 1), en, INF);
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
    for (auto *e : adj[now]) {
      int next = e->v;
      if (prv[next] == -1 && e->residual() > 0) {
        q.push(next);
        prv[next] = now;
        path[next] = e;
      }
    }
  }
}
ll flow(int st, int en) {
  ll block = INF;
  for (int i = en; i != st; i = prv[i]) {
    block = min(block, path[i]->residual());
  }
  for (int i = en; i != st; i = prv[i]) {
    path[i]->addFlow(block);
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
    
    graph_modeling();

    ll total = maxFlow(st, en);
    // cout << total << '\n';
    cout << total % (int)1e7;
}
