#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAXV = 20202;
const int INF = 1e9 + 7;

const int dy[] = {1, 0, -1, 0};
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

int n, k;
vector<string> a;
vector<edge *> adj[MAXV + 5];
int prv[MAXV + 5];
edge *path[MAXV + 5];

int st, en;

void input() {
    cin >> n >> k;
    a.resize(n);
    for (auto &i : a) cin >> i;
}

void add_edge(int n1, int n2, int cap) {
    edge *e1 = new edge(n2, cap), *e2 = new edge(n1, 0);
    e1->dual = e2, e2->dual = e1;
    adj[n1].push_back(e1);
    adj[n2].push_back(e2);
}

inline int Hash(int y, int x, bool is_in) { return (100 * y + x) * 2 + is_in; }

void build_graph() {
    st = MAXV - 2, en = MAXV - 1;

    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            if (a[y][x] == '+') continue;
            
            for (int d = 0; d < 4; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (ny < 0 || n <= ny || nx < 0 || n <= nx) continue;
                if (a[ny][nx] == '+') continue;
                add_edge(Hash(y, x, 0), Hash(ny, nx, 1), INF);
            }

            if (a[y][x] == '.') {
                add_edge(Hash(y, x, 1), Hash(y, x, 0), 1);
            } else if (a[y][x] == 'X') {
                add_edge(Hash(y, x, 0), en, INF);
                add_edge(Hash(y, x, 1), Hash(y, x, 0), INF);
            } else if (a[y][x] == 'O') {
                add_edge(st, Hash(y, x, 1), INF);
                add_edge(Hash(y, x, 1), Hash(y, x, 0), INF);
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

    build_graph();

    ll ans = maxFlow(st, en);

    if (ans <= k) {
        cout << "Yes\n";
        cout << ans;
    } else cout << "No";
}
