#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define Line pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()

const int MAXN = 303030;

const Line e = {0, -1e18};
struct LiChaoTree {
  ll f(Line l, ll x) { return l.first * x + l.second; }
  struct Node {
    ll xl, xr;
    int l, r;
    Line line;
  };
  vector<Node> t;
  vector<vector<pair<int, Node>>> stk;
  void build(ll xlb, ll xub) {
    t.push_back({xlb, xub, -1, -1, e});
  }
  void insert(Line newLine, int n = 0) {
    if (n == 0) stk.push_back(vector<pair<int, Node>>(0));
    
    ll xl = t[n].xl, xr = t[n].xr;
    ll xmid = (xl + xr) >> 1;

    Line llow = t[n].line, lhigh = newLine;
    if (f(llow, xl) >= f(lhigh, xl)) swap(llow, lhigh);

    if (f(llow, xr) <= f(lhigh, xr)) {
      stk.back().push_back({n, t[n]});
      t[n].line = lhigh;
      return;
    } else if (f(llow, xmid) < f(lhigh, xmid)) {
      stk.back().push_back({n, t[n]});
      t[n].line = lhigh;
      if (t[n].r == -1) {
        t[n].r = sz(t);
        t.push_back({xmid + 1, xr, -1, -1, e});
      }
      insert(llow, t[n].r);
    } else if (f(llow, xmid) >= f(lhigh, xmid)) {
      stk.back().push_back({n, t[n]});
      t[n].line = llow;
      if (t[n].l == -1) {
        t[n].l = sz(t);
        t.push_back({xl, xmid, -1, -1, e});
      }
      insert(lhigh, t[n].l);
    }
  }
  ll query(ll x, int n = 0) {
    if (n == -1) return e.second;
    ll xl = t[n].xl, xr = t[n].xr;
    ll xmid = (xl + xr) >> 1;

    ll ret = f(t[n].line, x);
    if (x <= xmid) ret = max(ret, query(x, t[n].l));
    else ret = max(ret, query(x, t[n].r));
    return ret;
  }
  void restore() {
    assert(!stk.empty());
    for (auto& i : stk.back()) t[i.fr] = i.sc;
    stk.pop_back();
  }
} lct;

int flag;
struct Seg {
    vector<vector<pll>> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void modify(int l, int r, pll val, int n = 1, int nl = 1, int nr = flag) {
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            t[n].push_back(val);
            return;
        }
        int mid = (nl + nr) >> 1;
        modify(l, r, val, n << 1, nl, mid);
        modify(l, r, val, n << 1 | 1, mid + 1, nr);
    }
} seg;

int m, op[MAXN];
map<int, pll> mp;
ll a[MAXN];
ll ans1[MAXN];
bool ans2[MAXN];

void input() {
    cin >> m;
    for (int i = 1; i <= m; i++) {
        cin >> op[i];
        if (op[i] == 1) {
            int x, y;
            cin >> x >> y;
            mp[i] = {x, y};
        }
        if (op[i] == 2) {
            int x; cin >> x;
            seg.modify(x, i, mp[x]);
            mp.erase(x);
        }
        if (op[i] == 3) cin >> a[i];
    }
    for (auto it : mp) seg.modify(it.fr, m, it.sc);
}

void odc(int n = 1, int nl = 1, int nr = flag) {
    int cnt = 0;
    for (auto& i : seg.t[n]) {
        cnt++;
        lct.insert(i);
    }

    if (nl == nr) {
        if (nr <= m && op[nl] == 3) {
            if (lct.stk.empty()) ans2[nl] = 1;
            else ans1[nl] = lct.query(a[nl]);
        }
        while (cnt--) lct.restore();
        return;
    }

    int mid = (nl + nr) >> 1;
    odc(n << 1, nl, mid);
    odc(n << 1 | 1, mid + 1, nr);

    while (cnt--) lct.restore();
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    lct.build(-(ll)1e9, (ll)1e9);
    seg.build(MAXN);

    input();

    odc();

    for (int i = 1; i <= m; i++) {
        if (op[i] != 3) continue;
        if (ans2[i]) cout << "EMPTY\n";
        else cout << ans1[i] << '\n';
    }
}
