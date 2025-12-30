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

constexpr ll INF = 1e18;

int flag; // array size
// 4. Segment Tree with Lazy Propagation
struct SegLazy { // 1-indexed
  const pll e = {0, -INF};
  vector<ll> t;
  vector<pll> lazy;
  void build(int n) {
    for (flag = 1; flag < n; flag <<= 1);
    t.assign(2 * flag, -INF);
    for (int i = 1; i < flag + n; i++) t[i] = 0;
    lazy.assign(2 * flag, e);
  }
  // modify a value to all elements in interval [l, r]
  void modify(int l, int r, pll value, int n = 1, int nl = 1, int nr = flag) {
    propagate(n, nl, nr);
    if (r < nl || nr < l) return;
    if (l <= nl && nr <= r) {
      lazy[n] = value;
      propagate(n, nl, nr);
      return;
    }
    int mid = (nl + nr) >> 1;
    modify(l, r, value, n << 1, nl, mid);
    modify(l, r, value, n << 1 | 1, mid + 1, nr);
    t[n] = max(t[n << 1], t[n << 1 | 1]);
  }
  ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) { // sum on interval [l, r]
    propagate(n, nl, nr);
    if (r < nl || nr < l) return -INF;
    if (l <= nl && nr <= r) return t[n];
    int mid = (nl + nr) / 2;
    return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
  }
  void propagate(int n, int nl, int nr) {
    if (lazy[n] != e) {
      if (n < flag) {
        lazy[n << 1].fr += lazy[n].fr;
        lazy[n << 1].sc += lazy[n].fr;
        lazy[n << 1].sc = max(lazy[n << 1].sc, lazy[n].sc);
        lazy[n << 1 | 1].fr += lazy[n].fr;
        lazy[n << 1 | 1].sc += lazy[n].fr;
        lazy[n << 1 | 1].sc = max(lazy[n << 1 | 1].sc, lazy[n].sc);
      }
      t[n] += lazy[n].fr;
      t[n] = max(t[n], lazy[n].sc);
      lazy[n] = e;
    }
  }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<ll> v(n + 1);
        vector<int> a(n + 1), b(n + 1);
        vector<int> b_inv(n + 1);

        for (int i = 1; i <= n; i++) cin >> v[i];
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) {
            cin >> b[i];
            b_inv[b[i]] = i;
        }

        SegLazy seg{};
        seg.build(n + 1);

        ll ans = 0;

        for (int i = 1; i <= n; i++) {
            int idx = b_inv[a[i]];
            seg.modify(0 + 1, (idx - 1) + 1, {v[a[i]], -INF});

            ll res = seg.query(0 + 1, (idx - 1) + 1);
            seg.modify((idx - 1) + 2, n + 1, {0, res});

            ans = max(ans, seg.query(1, n + 1));
        }

        cout << ans << '\n';
    }
}
