#pragma GCC optimize("O3")
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

// what: point update + range sum on a fixed-size array using a tree.
// time: build O(n), update/query O(log n); memory: O(n)
// constraint: 1-indexed [1, n]; a[0] unused.
// usage: seg_tree st; st.build(a); st.set(p, v); st.query(l, r);
struct seg_tree {
    int flag;
    vector<ll> t;
    void build(int n) {
        // goal: build tree from 1-indexed array.
        flag = 1;
        while (flag < n) flag <<= 1;
        t.assign(2 * flag, INF);
    }
    void set(int p, ll val) {
        // goal: set a[p] = val.
        p += flag - 1;
        for (t[p] = min(t[p], val); p > 1; p >>= 1)
            t[p >> 1] = min(t[p], t[p ^ 1]);
    }
    ll query(int l, int r) const { return query(l, r, 1, 1, flag); }
    ll query(int l, int r, int v, int nl, int nr) const {
        // result: sum on [l, r] within node range.
        if (r < nl || nr < l) return INF;
        if (l <= nl && nr <= r) return t[v];
        int mid = (nl + nr) >> 1;
        return min(query(l, r, v << 1, nl, mid), query(l, r, v << 1 | 1, mid + 1, nr));
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n, m, k;
        cin >> n >> m >> k;

        vector<int> l(m), r(m);
        for (int i = 0; i < m; i++) {
            cin >> l[i] >> r[i];
        }

        vector<int> ps(n + 2);
        vector<int> ps0(n + 2), ps1(n + 2), ps2(n + 2);
        for (int i = 0; i < m; i++) {
            ps[l[i]]++;
            ps[r[i] + 1]--;
        }
        for (int i = 1; i <= n; i++) {
            ps[i] += ps[i - 1];

            ps0[i] = (ps[i] == 0) + ps0[i - 1];
            ps1[i] = (ps[i] == 1) + ps1[i - 1];
            ps2[i] = (ps[i] == 2) + ps2[i - 1];
        }

        vector<int> ord(m);
        iota(all(ord), 0);
        sort(all(ord), [&](int i, int j) {
            return l[i] < l[j];
        });

        seg_tree seg;
        seg.build(n);

        int jj = 0;
        for (int ii = 0; ii < m; ii++) {
            int i = ord[i];

            while (jj < sz(ord)) {
                int j = ord[jj];
                if (l[j] <= l[i]) {
                    int res = ps1[r[j]] - ps1[l[j] - 1];
                    seg.set(r[j], res);
                    jj++;
                } else {
                    break;
                }
            }

            
        }
    }
}