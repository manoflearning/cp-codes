#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 202020;

int flag;    // array size
struct Seg { // 1-indexed
  vector<ll> t;
  void build(int n) {
    for (flag = 1; flag < n; flag <<= 1);
    t.resize(2 * flag);
    // for (int i = flag; i < flag + n; i++) cin >> t[i];
    // for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
  }
  void add(int p, ll value) { // set value at position p
    for (t[p += flag - 1] += value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
  }
  ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) { // sum on interval [l, r]
    if (r < nl || nr < l) return 0;
    if (l <= nl && nr <= r) return t[n];
    int mid = (nl + nr) / 2;
    return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
  }
} seg1, seg2;

int n, t;
vector<pii> a;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> t;
    for (int i = 1; i <= n; i++) {
        int l, r;
        cin >> l >> r;
        a.push_back({l, r});
    }

    vector<int> cc(1, -1);
    for (int i = 0; i < n; i++) {
        cc.push_back(a[i].fr);
        cc.push_back(a[i].fr + t);
        cc.push_back(a[i].sc);
    }
    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());
    for (int i = 0; i < n; i++) {
        a[i].fr = lower_bound(all(cc), a[i].fr) - cc.begin();
        a[i].sc = lower_bound(all(cc), a[i].sc) - cc.begin();
    }

    sort(all(a));

    seg1.build(sz(cc));
    seg2.build(sz(cc));

    for (int i = 0; i < n; i++) {
        seg1.add(a[i].sc, 1);
        // cout << a[i].sc << '\n';
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (i == 0 || (i > 0 && a[i].fr != a[i - 1].fr)) {
            int lb = a[i].fr;
            int ub = lower_bound(all(cc), cc[a[i].fr] + t) - cc.begin() - 1;
            
            int res = seg1.query(lb, ub) - seg2.query(ub + 1, sz(cc));
            // cout << i << ' ' << seg1.query(lb, ub) << ' ' << seg2.query(ub + 1, sz(cc)) << '\n';
            ans = max(ans, res);
        }

        seg1.add(a[i].sc, -1);
        seg2.add(a[i].sc, 1);
    }

    cout << ans;
}
