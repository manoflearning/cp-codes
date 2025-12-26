#pragma GCC optimize("Ofast")
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

constexpr int INF = 1e9 + 7;
constexpr int UB = 250'000;

int flag;
struct SegLazy { // 1-indexed
  vector<int> t, lazy;
  void build(int n) {
    for (flag = 1; flag < n; flag <<= 1);
    t.resize(2 * flag, INF);
    lazy.resize(2 * flag, INF);
  }
  // add a value to all elements in interval [l, r]
  void modify(int l, int r, int value, int n = 1, int nl = 1, int nr = flag) {
    propagate(n);
    if (r < nl || nr < l) return;
    if (l <= nl && nr <= r) {
      lazy[n] = min(lazy[n], value);
      propagate(n);
      return;
    }
    int mid = (nl + nr) >> 1;
    modify(l, r, value, n << 1, nl, mid);
    modify(l, r, value, n << 1 | 1, mid + 1, nr);
    t[n] = min(t[n << 1], t[n << 1 | 1]);
  }
  int query(int l, int r, int n = 1, int nl = 1, int nr = flag) { // sum on interval [l, r]
    propagate(n);
    if (r < nl || nr < l) return INF;
    if (l <= nl && nr <= r) return t[n];
    int mid = (nl + nr) / 2;
    return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
  }
  void propagate(int n) {
    if (lazy[n] != INF) {
      if (n < flag) {
        lazy[n << 1] = min(lazy[n << 1], lazy[n]);
        lazy[n << 1 | 1] = min(lazy[n << 1 | 1], lazy[n]);
      }
      t[n] = min(t[n], lazy[n]);
      lazy[n] = INF;
    }
  }
};

int n, m;
vector<vector<bool>> a;
vector<vector<int>> ans;
vector<SegLazy> seg;

void init() {
    a.clear();
    ans.clear();
    seg.clear();
}

void input() {
    cin >> n >> m;
    a.resize(n, vector<bool>(m));
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        for (int j = 0; j < m; j++) {
            a[i][j] = (s[j] == '1');
        }
    }
}

void coloring(int sty, int stx, int eny, int enx) {
    int co = (eny - sty + 1) * (enx - stx + 1);

    for (int x = stx; x <= enx; x++) {
        seg[x].modify(sty + 1, eny + 1, co);
    }
    // for (int y = sty; y <= eny; y++) {
    //     for (int x = stx; x <= enx; x++) {
    //         ans[y][x] = min(ans[y][x], co);
    //     }
    // }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();
        
        input();

        bool is_swaped = 0;
        if (n < m) {
            is_swaped = 1;
            vector<vector<bool>> tmp(m, vector<bool>(n));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    tmp[j][i] = a[i][j];
                }
            }
            swap(n, m);
            a = tmp;
        }
        
        ans.resize(n, vector<int>(m));
        seg.resize(m);
        for (int i = 0; i < m; i++) {
            seg[i].build(n);
        }

        for (int len = 2; len <= m; len++) {
            vector<int> mp(m, -1);
            for (int eny = 0; eny < n; eny++) {
                for (int stx = 0; stx + len - 1 < m; stx++) {
                    int enx = stx + len - 1;
                    if (a[eny][stx] && a[eny][enx]) {
                        if (mp[stx] != -1) {
                            int sty = mp[stx];
                            coloring(sty, stx, eny, enx);
                        }
                        mp[stx] = eny;
                    }
                }
            }
        }

        for (int y = 0; y < n; y++) {
            for (int x = 0; x < m; x++) {
                ans[y][x] = seg[x].query(y + 1, y + 1);
            }
        }

        if (is_swaped) {
            vector<vector<int>> tmp(m, vector<int>(n));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    tmp[j][i] = ans[i][j];
                }
            }
            swap(n, m);
            ans = tmp;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << (ans[i][j] == INF ? 0 : ans[i][j]) << ' ';
            }
            cout << '\n';
        }
    }
}
