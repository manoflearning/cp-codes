#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr int INF = 1e9 + 7;

// 2. 2D Segment Tree with Coordinate Compression
// You must perform all fake_* calls first, then call prepare(), and only after that call modify and query
struct Seg2DComp { // 0-indexed
  int n;
  vector<vector<int>> a;
  vector<vector<int>> used;
  Seg2DComp(int n) : n(n), a(2 * n), used(2 * n) {}
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
      a[i].resize(sz(used[i]) << 1);
    }
  }
  void modify(int x, int y) {
    for (x += n; x >= 1; x >>= 1) {
      int i = lower_bound(all(used[x]), y) - used[x].begin() + sz(used[x]);
      for (a[x][i]++; i > 1; i >>= 1) {
        a[x][i >> 1] = a[x][i] + a[x][i ^ 1];
      }
    }
  }
  int query1D(int x, int y1, int y2) {
    int ret = 0;
    y1 = lower_bound(all(used[x]), y1) - used[x].begin();
    y2 = lower_bound(all(used[x]), y2) - used[x].begin();
    for (y1 += sz(used[x]), y2 += sz(used[x]) + 1; y1 < y2; y1 >>= 1, y2 >>= 1) {
      if (y1 & 1) ret += a[x][y1++];
      if (y2 & 1) ret += a[x][--y2];
    }
    return ret;
  }
  // sum on rectangle [x1, x2] × [y1, y2] (0-indexed, inclusive)
  int query(int x1, int x2, int y1, int y2) {
    int ret = 0;
    for (x1 += n, x2 += n + 1; x1 < x2; x1 >>= 1, x2 >>= 1) {
      if (x1 & 1) ret += query1D(x1++, y1, y2);
      if (x2 & 1) ret += query1D(--x2, y1, y2);
    }
    return ret;
  }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        int mn_x = INF, mx_x = -INF;
        int mn_y = INF, mx_y = -INF;
        vector<pii> a(n);
        for (auto &i : a) {
            cin >> i.fr >> i.sc;
            mn_x = min(mn_x, i.fr);
            mx_x = max(mx_x, i.fr);
            mn_y = min(mn_y, i.sc);
            mx_y = max(mx_y, i.sc);
        }

        vector<int> cc_x, cc_y;
        for (auto &i : a) {
            cc_x.push_back(i.fr);
            cc_y.push_back(i.sc);
        }
        sort(all(cc_x));
        sort(all(cc_y));
        cc_x.erase(unique(all(cc_x)), cc_x.end());
        cc_y.erase(unique(all(cc_y)), cc_y.end());
        for (auto &i : a) {
            i.fr = lower_bound(all(cc_x), i.fr) - cc_x.begin() + 1;
            i.sc = lower_bound(all(cc_y), i.sc) - cc_y.begin() + 1;
        }

        Seg2DComp seg{n};
        for (auto &i : a) {
            seg.fake_modify(i.fr, i.sc);

            seg.fake_query(i.fr, mx_x, i.sc, mx_y);
            seg.fake_query(mn_x, i.fr - 1, i.sc, mx_y);
            seg.fake_query(i.fr, mx_x, mn_y, i.sc - 1);
            // seg.fake_query(mn_x, i.fr - 1, mn_y, i.sc - 1);
        }
        seg.prepare();

        for (auto &i : a) {
            seg.modify(i.fr, i.sc);
        }

        int ans = 0;
        pii opt = {0, 0};
        for (auto &i : a) {
            int res1 = seg.query(i.fr, mx_x, i.sc, mx_y);
            int res2 = seg.query(mn_x, i.fr - 1, i.sc, mx_y);
            int res3 = seg.query(i.fr, mx_x, mn_y, i.sc - 1);
            int res4 = n - (res1 + res2 + res3);

            int res = min({res1, res2, res3, res4});
            if (ans < res) {
                ans = res;
                opt = {i.fr, i.sc};
            }
        }

        cout << ans << '\n';
        cout << opt.fr << ' ' << opt.sc << '\n';
    }
}
