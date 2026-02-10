#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int INF = 1e9 + 7;
constexpr int dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
constexpr int dy[] = {1, 0, -1, 0, 1, -1, 1, -1};

int _hash(const int x, const int y, const int n) { return x + y * n; }

vector<int> get_dominator_tree(const vector<vector<int>> &g, int src){ // // 0-based
  int n = g.size();
  vector<vector<int>> rg(n), buf(n);
  vector<int> r(n), val(n), idom(n, -1), sdom(n, -1), o, p(n), u(n);
  iota(all(r), 0); iota(all(val), 0);
  for(int i=0; i<n; i++) for(auto j : g[i]) rg[j].push_back(i);
  function<int(int)> find = [&](int v){
    if(v == r[v]) return v;
    int ret = find(r[v]);
    if(sdom[val[v]] > sdom[val[r[v]]]) val[v] = val[r[v]];
    return r[v] = ret;
  };
  function<void(int)> dfs = [&](int v){
    sdom[v] = o.size(); o.push_back(v);
    for(auto i : g[v]) if(sdom[i] == -1) p[i] = v, dfs(i);
  };
  dfs(src); reverse(all(o));
  for(auto &i : o){
    if(sdom[i] == -1) continue;
    for(auto j : rg[i]){
      if(sdom[j] == -1) continue;
      int x = val[find(j), j];
      if(sdom[i] > sdom[x]) sdom[i] = sdom[x];
    }
    buf[o[o.size() - sdom[i] - 1]].push_back(i);
    for(auto j : buf[p[i]]) u[j] = val[find(j), j];
    buf[p[i]].clear();
    r[i] = p[i];
  }
  reverse(all(o)); idom[src] = src;
  for(auto i : o){ // WARNING : if different, takes idom
    if(i != src) idom[i] = sdom[i] == sdom[u[i]] ? sdom[i] : idom[u[i]];
  }
  for(auto i : o) if(i != src) idom[i] = o[idom[i]];
  return idom; // unreachable -> ret[i] = -1
}

vector<vector<int>> build_graph(const int n, const int m, const vector<string> &a) {
    vector<vector<int>> ret(n * m);
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            if (a[x][y] == 'X') continue;
            for (int d = 0; d < 4; d++) {
                const int nx = x + dx[d], ny = y + dy[d];
                if (nx < 0 || n <= nx || ny < 0 || m <= ny) continue;
                if (a[nx][ny] == 'X') continue;
                ret[_hash(x, y, n)].push_back(_hash(nx, ny, n));
            }
        }
    }
    return std::move(ret);
}

vector<int> bfs(const vector<vector<int>> &g) {
    vector<int> dist(sz(g), -1);
    queue<int> qu;
    dist[0] = 0;
    qu.push(0);
    while (!qu.empty()) {
        int now = qu.front();
        qu.pop();
        for (const int nxt : g[now]) {
            if (dist[nxt] != -1) continue;
            dist[nxt] = dist[now] + 1;
            qu.push(nxt);
        }
    }
    return std::move(dist);
}

vector<vector<int>> get_bfs_dag(const vector<vector<int>> &g, const vector<int> &dist) {
    vector<vector<int>> ret(sz(g));
    for (int now = 0; now < sz(g); now++) {
        for (const int nxt : g[now]) {
            if (dist[nxt] == dist[now] + 1) {
                ret[now].push_back(nxt);
            }
        }
    }
    return std::move(ret);
}

struct UF {
    vector<int> e;
    vector<pii> st;
    UF(int n) {
        e.assign(n, -1);
    }
    int find(int x) { return e[x] < 0 ? x : find(e[x]); }
    int time() { return sz(st); }
    void rollback(int t) {
        for (int i = time(); i --> t; )
            e[st[i].first] = st[i].second;
        st.resize(t);
    }
    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (e[u] > e[v]) swap(u, v);
        st.push_back({u, e[u]});
        st.push_back({v, e[v]});
        e[u] += e[v], e[v] = u;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vector<string> a(n);
    for (auto &i : a) cin >> i;

    vector<vector<int>> g_base{build_graph(n, m, a)};

    vector<int> dist{bfs(g_base)};

    vector<vector<int>> g_bfs{get_bfs_dag(g_base, dist)};

    vector<int> par{get_dominator_tree(g_bfs, 0)};

    UF uf{n * m + 2};
    const int dl = n * m;
    const int ur = n * m + 1;
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            if (a[x][y] == '.') continue;
            for (int d = 0; d < 8; d++) {
                const int nx = x + dx[d], ny = y + dy[d];
                if (nx < 0 || n <= nx || ny < 0 || m <= ny) continue;
                if (a[nx][ny] == '.') continue;
                uf.merge(_hash(x, y, n), _hash(nx, ny, n));
            }
            if (x == n - 1 || y == 0) uf.merge(_hash(x, y, n), dl);
            if (x == 0 || y == m - 1) uf.merge(_hash(x, y, n), ur);
        }
    }

    assert(uf.find(dl) != uf.find(ur));

    auto ans = a;

    int now = par[_hash(n - 1, m - 1, n)];
    while (now > 0) {
        const int snapshot = uf.time();

        const int x = now % n, y = now / n;
        for (int d = 0; d < 8; d++) {
            const int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || n <= nx || ny < 0 || m <= ny) continue;
            if (a[nx][ny] == '.') continue;
            uf.merge(_hash(x, y, n), _hash(nx, ny, n));
        }
        if (x == n - 1 || y == 0) uf.merge(_hash(x, y, n), dl);
        if (x == 0 || y == m - 1) uf.merge(_hash(x, y, n), ur);

        if (uf.find(dl) != uf.find(ur)) ans[x][y] = '*';
        uf.rollback(snapshot);

        if (par[now] == now) break;
        now = par[now];
    }

    for (const auto &i : ans)
        cout << i << '\n';
}
