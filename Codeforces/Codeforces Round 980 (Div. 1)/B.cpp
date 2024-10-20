#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define all(x) (x).begin(), (x).end()

const ll INF = 1e18;

int flag;    // array size
struct Seg { // 1-indexed
  vector<ll> t, lazy;
  void build(int n) {
    t.clear();
    lazy.clear();
    for (flag = 1; flag < n; flag <<= 1);
    t.resize(2 * flag, INF);
    lazy.resize(2 * flag, INF);
    // for (int i = flag; i < flag + n; i++) cin >> t[i];
    // for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
  }
  // add a value to all elements in interval [l, r]
  void modify(int l, int r, ll value, int n = 1, int nl = 1, int nr = flag) {
    propagate(n, nl, nr);
    if (r < nl || nr < l) return;
    if (l <= nl && nr <= r) {
      lazy[n] = min(lazy[n], value);
      propagate(n, nl, nr);
      return;
    }
    int mid = (nl + nr) >> 1;
    modify(l, r, value, n << 1, nl, mid);
    modify(l, r, value, n << 1 | 1, mid + 1, nr);
    t[n] = min(t[n << 1], t[n << 1 | 1]);
  }
  ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) { // sum on interval [l, r]
    propagate(n, nl, nr);
    if (r < nl || nr < l) return INF;
    if (l <= nl && nr <= r) return t[n];
    int mid = (nl + nr) / 2;
    return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
  }
  void propagate(int n, int nl, int nr) {
    if (lazy[n] != INF) {
      if (n < flag) {
        lazy[n << 1] = min(lazy[n << 1], lazy[n]);
        lazy[n << 1 | 1] = min(lazy[n << 1 | 1], lazy[n]);
      }
      t[n] = min(t[n], lazy[n]);
    //   t[n] += lazy[n] * (nr - nl + 1);
      lazy[n] = INF;
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

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;
        vector<int> a(n + 1), b(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];

        ll ans = 0;

        seg.build(n);
        seg.modify(1, 1, 0);
        
        ll psum = 0;
        for (int i = 1; i <= n; i++) {
            psum += a[i];
            ans = max(ans, psum - seg.query(i, i));
            if (i < b[i])
                seg.modify(i + 1, b[i], seg.query(i, i) + a[i]);
        }

        cout << ans << '\n';

        // vector<ll> minb(n + 1, INF);

        // ll ans = 0;

        // ll acc = 0;

        // priority_queue<int> idxs;
        // idxs.push(1);
        // acc += a[1];
        // minb[b[1]] = min<ll>(minb[b[1]], a[1]);

        // priority_queue<int, vector<int>, greater<int>> to_go;
        // for (int i = 2; i <= n; i++) to_go.push(i);
        
        // while (!idxs.empty()) {
        //     int i = idxs.top();
        //     idxs.pop();

        //     ans = max(ans, acc);
            
        //     if (b[i] <= i) continue;

        //     acc -= minb[b[i]];

        //     while (!to_go.empty() && to_go.top() <= b[i]) {
        //         int j = to_go.top(); to_go.pop();
        //         idxs.push(j);
        //         acc += a[j];
        //         minb[b[j]] = min<ll>(minb[b[j]], a[j]);
        //     }

        //     // if (cntb[b[i]] >= 1) {
        //     //     while (!idxs.empty()) {
        //     //         int j = idxs.top();
        //     //         if (b[j] == b[i]) break;
        //     //         idxs.pop();
        //     //         cntb[b[j]]--;
        //     //     }
        //     //     assert(!idxs.empty());
        //     // } else {
        //     //     acc -= a[i];
                
        //     // }
        // }

        // cout << ans << '\n';
    }
}

// if b[i] < i => always solve problem i
// so if we skip the problem
// => maximum index is increasing
// => 