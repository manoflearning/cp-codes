#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const ll INF = 1e18;

int flag;    // array size
struct Seg { // 1-indexed
  vector<ll> t, lazy;
  void build(int n) {
    for (flag = 1; flag < n; flag <<= 1);
    t.resize(2 * flag);
    lazy.resize(2 * flag);
  }
  // add a value to all elements in interval [l, r]
  void modify(int l, int r, ll value, int n = 1, int nl = 1, int nr = flag) {
    propagate(n, nl, nr);
    if (r < nl || nr < l) return;
    if (l <= nl && nr <= r) {
      lazy[n] += value;
      propagate(n, nl, nr);
      return;
    }
    int mid = (nl + nr) >> 1;
    modify(l, r, value, n << 1, nl, mid);
    modify(l, r, value, n << 1 | 1, mid + 1, nr);
    t[n] = t[n << 1] + t[n << 1 | 1];
  }
  ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) { // sum on interval [l, r]
    propagate(n, nl, nr);
    if (r < nl || nr < l) return 0;
    if (l <= nl && nr <= r) return t[n];
    int mid = (nl + nr) / 2;
    return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
  }
  void propagate(int n, int nl, int nr) {
    if (lazy[n] != 0) {
      if (n < flag) {
        lazy[n << 1] += lazy[n];
        lazy[n << 1 | 1] += lazy[n];
      }
      t[n] += lazy[n] * (nr - nl + 1);
      lazy[n] = 0;
    }
  }
} seg;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; ll m;
    cin >> n >> m;

    ll ans = m;

    vector<pll> a;
    for (int i = 0; i < n; i++) {
        ll s, t;
        cin >> s >> t;

        if (s >= t) ans += 2 * (s - t);
        else a.push_back({s, t});
    }

    if (!a.empty()) {
        vector<ll> cc(1, -INF);
        for (auto [l, r] : a) {
            cc.push_back(l);
            cc.push_back(r);
        }

        sort(all(cc));
        cc.erase(unique(all(cc)), cc.end());

        for (auto [l, r] : a) {
            l = lower_bound(all(cc), l) - cc.begin();
            r = lower_bound(all(cc), r) - cc.begin();


        }
    }

    cout << ans;
}
