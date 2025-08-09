// 다음의 다이나믹 세그먼트 트리 공개 소스코드를 사용했습니다:
// https://github.com/manoflearning/cp-reference-codes/blob/master/1-data-structure/segment_tree.cpp

// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(c) (c).begin(), (c).end()

const int N = 202020;

const int MAXL = 1, MAXR = 1'000'000'000;
const int INF = 1e9 + 7;

struct Node {
  ll x;
  int l, r;
};

struct Dyseg {
  vector<Node> t = {{-INF, -1, -1}, {-INF, -1, -1}};
  void build() {
    t.clear();
    t = {{-INF, -1, -1}, {-INF, -1, -1}};
  }
  void modify(int p, ll x, int n = 1, int nl = MAXL, int nr = MAXR) {
    if (p < nl || nr < p) return;
    t[n].x = max(t[n].x, x);
    if (nl < nr) {
      int mid = (nl + nr) >> 1;
      if (p <= mid) {
        if (t[n].l == -1) {
          t[n].l = sz(t);
          t.push_back({-INF, -1, -1});
        }
        modify(p, x, t[n].l, nl, mid);
      } else {
        if (t[n].r == -1) {
          t[n].r = sz(t);
          t.push_back({-INF, -1, -1});
        }
        modify(p, x, t[n].r, mid + 1, nr);
      }
    }
  }
  ll query(int l, int r, int n = 1, int nl = MAXL, int nr = MAXR) {
    if (n == -1) return -INF;
    if (r < nl || nr < l) return -INF;
    if (l <= nl && nr <= r) return t[n].x;
    int mid = (nl + nr) >> 1;
    ll ret = -INF;
    if (l <= mid && t[n].l != -1) {
    //   if (t[n].l == -1) {
    //     t[n].l = sz(t);
    //     t.push_back({0, -1, -1});
    //   }
      ret = max(ret, query(l, r, t[n].l, nl, mid));
    }
    if (mid + 1 <= r && t[n].r != -1) {
    //   if (t[n].r == -1) {
    //     t[n].r = sz(t);
    //     t.push_back({0, -1, -1});
    //   }
      ret = max(ret, query(l, r, t[n].r, mid + 1, nr));
    }
    return ret;
  }
} dyseg;

int n;
vector<ll> p, q, r;
int k1, k2;

void init() {
    dyseg.build();
    p.clear();
    q.clear();
    r.clear();
    k1 = k2 = -1;
}

void input() {
    cin >> n;

    set<ll> st;
    vector<ll> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        st.insert(b[i]);
    }

    assert(1 <= sz(st) && sz(st) <= 2);
    if (sz(st) == 2) {
        auto it = st.begin();
        k1 = *it, k2 = *(++it);
    } else {
        auto it = st.begin();
        k1 = *it, k2 = -1;
    }

    for (int i = 1; i <= n; i++) {
        if (b[i] == k1) p.push_back(a[i]);
        else q.push_back(a[i]);
        r.push_back(a[i]);
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        init();

        input();

        sort(all(p));
        sort(all(q));
        sort(all(r));

        int ans = 0;

        {   
            int j = 0;
            for (int i = 0; i < sz(r); i++) {
                while (j < sz(r) && r[j] - r[i] <= k1) j++;
                ans = max(ans, j - i);
            }
        }
        {
            for (int j = 0; j < sz(q); j++) {
                int res = 0;
                res += j;
                
                int ub = q[j];
                int lb1 = ub - k1;
                res -= lower_bound(all(p), lb1) - p.begin();

                if (lb1 >= 1) dyseg.modify(lb1, res);
            }

            int j = 0;
            for (int i = 0; i < sz(q); i++) {
                int lb = q[i];
                int ub1 = lb + k1;

                int fuck1 = upper_bound(all(p), ub1) - p.begin();

                int res1 = fuck1 + dyseg.query(lb, min({(int)1e9, ub1, lb + k2 - k1})) - i + 1;

                while (j < sz(q) && q[j] - q[i] <= k2) j++;
                int res2 = j - i;

                ans = max({ans, res1, res2});

                // for (int j = i; j < sz(q); j++) {
                //     int ub = q[j];
                //     if (ub - lb > k2) break;
                //     int lb1 = ub - k1;

                //     int res = 0;
                //     res += j - i + 1;
                //     if (lb1 <= ub1 && ub1 - lb1 <= k1) {
                //         int fuck2 = lower_bound(all(p), lb1) - p.begin();

                //         res += fuck1 - fuck2;
                //     }

                //     ans = max(ans, res);
                // }
            }
        }

        cout << ans << '\n';

        cout << flush;
    }
}
