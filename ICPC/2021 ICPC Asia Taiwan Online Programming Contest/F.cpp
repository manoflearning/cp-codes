#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 202020;

int n, q, a[MAXN];
ll mxlen[MAXN];

int flag;    // array size
struct Seg { // 1-indexed
  vector<ll> t, lazy;
  void build(int n) {
    for (flag = 1; flag < n; flag <<= 1);
    t.resize(2 * flag);
    lazy.resize(2 * flag);
    for (int i = flag; i < flag + n; i++) t[i] = mxlen[i - flag + 1];
    for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
  }
  // add a value to all elements in interval [l, r]
  void add(int l, int r, ll value, int n = 1, int nl = 1, int nr = flag) {
    propagate(n, nl, nr);
    if (r < nl || nr < l) return;
    if (l <= nl && nr <= r) {
      lazy[n] += value;
      propagate(n, nl, nr);
      return;
    }
    int mid = (nl + nr) >> 1;
    add(l, r, value, n << 1, nl, mid);
    add(l, r, value, n << 1 | 1, mid + 1, nr);
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

void input() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (i == 1 || (i > 1 && a[i - 1] == a[i])) mxlen[i] = 1;
        else mxlen[i] = 1 + mxlen[i - 1];
    }
}

int bs(int l, int r) {
    int st = l;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (seg.query(mid, mid) >= (mid - st + 1)) l = mid;
        else r = mid - 1;
    }
    return l;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    input();
    
    seg.build(n);

    while (q--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) {
            if (1 < l) {
                ll diff = 0;
                if (seg.query(l, l) == 1) {
                    diff = seg.query(l - 1, l - 1);
                } else {
                    diff = -seg.query(l - 1, l - 1);
                }

                int ub = bs(l, n);
                seg.add(l, ub, diff);
            }
            if (r < n) {
                ll diff = 0;
                if (seg.query(r + 1, r + 1) == 1) {
                    diff = seg.query(r, r);
                } else {
                    diff = -seg.query(r, r);
                }

                int ub = bs(r + 1, n);
                seg.add(r + 1, ub, diff);
            }
        }
        if (op == 2) {
            ll ub = bs(l, r);

            ll ans = 0;
            ans += (ub - l + 1) * (ub - l + 2) / 2;
            ans += seg.query(ub + 1, r);

            cout << ans << '\n';
        }
    }
}
