#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int N = 2020;
constexpr int M = 202020;
constexpr ll INF = 1e18;

// You must perform all fake_* calls first, then call prepare(), and only after that call modify and query
struct Seg2DLight { // 0-indexed
  int n;
  vector<vector<ll>> a;
  vector<vector<int>> used;
  Seg2DLight(int n) : n(n), a(2 * n), used(2 * n) {}
  void fake_modify(int x, int y) {
    for (x += n; x >= 1; x >>= 1)
      used[x].push_back(y);
  }
  void fake_query(int x1, int x2, int y1, int y2) {
    for (x1 += n, x2 += n + 1; x1 < x2; x1 >>= 1, x2 >>= 1) {
      if (x1 & 1) {
        used[x1].push_back(y1);
        used[x1++].push_back(y2);
      }
      if (x2 & 1) {
        used[--x2].push_back(y1);
        used[x2].push_back(y2);
      }
    }
  }
  void prepare() {
    for (int i = 0; i < 2 * n; i++) {
      if (!used[i].empty()) {
        sort(used[i].begin(), used[i].end());
        used[i].erase(unique(all(used[i])), used[i].end());
      }
      used[i].shrink_to_fit();
      a[i].resize(used[i].size() * 2, -INF);
    }
  }
  void modify(int x, int y, ll val) {
    for (x += n; x >= 1; x >>= 1) {
      int i = lower_bound(all(used[x]), y) - used[x].begin() + sz(used[x]);
      for (a[x][i] = max(a[x][i], val); i > 1; i >>= 1) {
        a[x][i >> 1] = max(a[x][i], a[x][i ^ 1]);
      }
    }
  }
  ll query1D(int x, int y1, int y2) {
    ll ret = -INF;
    y1 = lower_bound(all(used[x]), y1) - used[x].begin();
    y2 = lower_bound(all(used[x]), y2) - used[x].begin();
    for (y1 += sz(used[x]), y2 += sz(used[x]) + 1; y1 < y2; y1 >>= 1, y2 >>= 1) {
      if (y1 & 1) ret = max(ret, a[x][y1++]);
      if (y2 & 1) ret = max(ret, a[x][--y2]);
    }
    return ret;
  }
  // sum on rectangle [x1, x2] × [y1, y2] (0-indexed, inclusive)
  ll query(int x1, int x2, int y1, int y2) {
    ll ret = -INF;
    for (x1 += n, x2 += n + 1; x1 < x2; x1 >>= 1, x2 >>= 1) {
      if (x1 & 1) ret = max(ret, query1D(x1++, y1, y2));
      if (x2 & 1) ret = max(ret, query1D(--x2, y1, y2));
    }
    return ret;
  }
};

int n, m;
ll a[N], psum[N];
vector<tuple<ll, int, int>> b;

int s[M], e[M];
ll u[M];
vector<int> ord;
ll ans[M];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++)
        cin >> s[i] >> e[i] >> u[i];

    for (int i = 1; i <= n; i++)
        psum[i] = a[i] + psum[i - 1];

    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
            b.push_back({psum[j] - psum[i - 1], i, j});

    sort(all(b));
    
    ord.resize(m);
    iota(all(ord), 1);
    sort(all(ord), [&](int i, int j) {
        return u[i] < u[j];
    });

    Seg2DLight seg{n + 1};

    for (auto &[_, x, y] : b) {
      seg.fake_modify(x, y);
    }
    for (int i = 1; i <= m; i++) {
      seg.fake_query(s[i], e[i], s[i], e[i]);
    }
    seg.prepare();

    int idx = 0;
    for (const auto &i : ord) {
        while (idx < sz(b) && get<0>(b[idx]) <= u[i]) {
            auto [w, x, y] = b[idx++];
            seg.modify(x, y, w);
        }

        ans[i] = seg.query(s[i], e[i], s[i], e[i]);
    }

    for (int i = 1; i <= m; i++) {
        if (ans[i] == -INF) cout << "NONE\n";
        else cout << ans[i] << '\n';
    }
}