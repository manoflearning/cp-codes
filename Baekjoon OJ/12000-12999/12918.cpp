#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define sz(x) (int)(x).size()

constexpr ld INF = 1e18;
ld hungarian(int n, int m, const vector<vector<ld>> &a) {
  vector<ld> u(n + 1), v(m + 1);
  vector<int> p(m + 1), way(m + 1);
  for (int i = 1; i <= n; i++) {
    p[0] = i;
    int j0 = 0;
    vector<ld> minv(m + 1, INF);
    vector<bool> used(m + 1, 0);
    do {
      used[j0] = 1;
      int i0 = p[j0], j1;
      ld delta = INF;
      for (int j = 1; j <= m; j++)
        if (!used[j]) {
          ld cur = a[i0][j] - u[i0] - v[j];
          if (cur < minv[j])
            minv[j] = cur, way[j] = j0;
          if (minv[j] < delta)
            delta = minv[j], j1 = j;
        }
      for (int j = 0; j <= m; ++j)
        if (used[j])
          u[p[j]] += delta, v[j] -= delta;
        else
          minv[j] -= delta;
      j0 = j1;
    } while (p[j0] != 0);
    do {
      int j1 = way[j0];
      p[j0] = p[j1];
      j0 = j1;
    } while (j0);
  }
  return -v[0];
}

struct point { ll x, y; };

int n;
vector<point> l, r;
ld ans{};

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        if (x == 0) continue;

        if (x < 0) l.push_back(point{x, y});
        else r.push_back(point{x, y});
    }

    if (sz(l) > sz(r)) swap(l, r);

    for (auto &i : l) ans += abs(i.x);
    for (auto &i : r) ans += abs(i.x);

    vector<vector<ld>> a(sz(l) + 1, vector<ld>(sz(r) + 1));
    for (int i = 0; i < sz(l); i++) {
        for (int j = 0; j < sz(r); j++) {
            const point &p = l[i], &q = r[j];

            ld w = sqrt((ld)((p.x + q.x) * (p.x + q.x) + (p.y - q.y) * (p.y - q.y))) - abs(p.x - q.x);
            if (w > 0) continue;
            a[i + 1][j + 1] = w;
        }
    }

    cout << fixed;
    cout.precision(3);

    cout << ans + hungarian(sz(l), sz(r), a);
}
