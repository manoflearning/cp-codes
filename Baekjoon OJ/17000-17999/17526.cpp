#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define Line pair<ll, ll>

const Line e = {0, 1e18};
struct LiChaoTree {
  ll f(Line l, ll x) { return l.first * x + l.second; }
  struct Node {
    ll xl, xr;
    int l, r;
    Line line;
  };
  vector<Node> t;
  void build(ll xlb, ll xub) {
    t.push_back({xlb, xub, -1, -1, e});
  }
  void insert(Line newLine, int n = 0) {
    ll xl = t[n].xl, xr = t[n].xr;
    ll xmid = (xl + xr) >> 1;

    Line llow = t[n].line, lhigh = newLine;
    if (f(llow, xl) >= f(lhigh, xl)) swap(llow, lhigh);

    if (f(llow, xr) <= f(lhigh, xr)) {
      t[n].line = llow;
      return;
    } else if (f(llow, xmid) < f(lhigh, xmid)) {
      t[n].line = llow;
      if (t[n].r == -1) {
        t[n].r = sz(t);
        t.push_back({xmid + 1, xr, -1, -1, e});
      }
      insert(lhigh, t[n].r);
    } else if (f(llow, xmid) >= f(lhigh, xmid)) {
      t[n].line = lhigh;
      if (t[n].l == -1) {
        t[n].l = sz(t);
        t.push_back({xl, xmid, -1, -1, e});
      }
      insert(llow, t[n].l);
    }
  }
  ll query(ll x, int n = 0) {
    if (n == -1) return e.second;
    ll xl = t[n].xl, xr = t[n].xr;
    ll xmid = (xl + xr) >> 1;

    ll ret = f(t[n].line, x);
    if (x <= xmid) ret = min(ret, query(x, t[n].l));
    else ret = min(ret, query(x, t[n].r));
    return ret;
  }
} lct;

int n;
ll psum[101010];
ll a[101010], b[101010];
ll dp[101010];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 2; i <= n; i++) {
        int x; cin >> x;
        psum[i] = x + psum[i - 1];
    }
    for (int i = 1; i < n; i++)
        cin >> b[i] >> a[i];

    lct.build(-1'000'000'000'000ll, 1'000'000'000'000ll);
    lct.insert({a[1], b[1]});

    for (int i = 2; i <= n; i++) {
        dp[i] = lct.query(psum[i]);
		lct.insert({a[i], -a[i] * psum[i] + b[i] + dp[i]});
    }

    cout << dp[n];
}
