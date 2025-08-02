#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(x) (x).begin(), (x).end()

int flag;    // array size
struct Seg { // 1-indexed
  vector<ll> t;
  void build(int n) {
    for (flag = 1; flag < n; flag <<= 1);
    t.resize(2 * flag);
    // for (int i = flag; i < flag + n; i++) cin >> t[i];
    // for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
  }
  void modify(int p, ll value) { // set value at position p
    for (t[p += flag - 1] = value; p > 1; p >>= 1) {
      t[p >> 1] = max(t[p], t[p ^ 1]);
    }
  }
  ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) { // sum on interval [l, r]
    if (r < nl || nr < l) return 0;
    if (l <= nl && nr <= r) return t[n];
    int mid = (nl + nr) / 2;
    return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
  }
} seg;

int n, m, t;
struct Cat { int r, c; };
vector<Cat> a;

void coor_comp() {
    vector<int> y, x;

    y.push_back(0);
    x.push_back(0);
    for (auto &i : a) {
        y.push_back(i.r);
        x.push_back(i.c);
    }
    y.push_back(n);
    x.push_back(m);

    sort(all(y)); sort(all(x));
    y.erase(unique(all(y)), y.end());
    x.erase(unique(all(x)), x.end());

    for (auto &i : a) {
        i.r = lower_bound(all(y), i.r) - y.begin() + 1;
        i.c = lower_bound(all(x), i.c) - x.begin() + 1;
    }
    n = lower_bound(all(y), n) - y.begin() + 1;
    m = lower_bound(all(x), m) - x.begin() + 1;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> m >> t;
    a.resize(t);
    for (auto &i : a) {
        cin >> i.r >> i.c;
    }

    coor_comp();

    sort(all(a), [](const Cat &i, const Cat &j) {
        return i.r ^ j.r ? i.r > j.r : i.c > j.c;
    });

    seg.build(m);

    for (auto &[r, c] : a) {
        if (r < 1 || n < r || c < 1 || m < c) continue;
        int res = seg.query(c, m);
        seg.modify(c, res + 1);
    }

    cout << seg.query(1, m);
}
