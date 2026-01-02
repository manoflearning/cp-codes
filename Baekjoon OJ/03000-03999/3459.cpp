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
        t[p + flag - 1] = min(t[p + flag - 1], val);
        for (p += flag - 1; p > 1; p >>= 1)
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

    int n, m;
    cin >> n >> m;

    vector<int> l(m), r(m);
    for (int i = 0; i < m; i++)
        cin >> l[i] >> r[i];

    int l_mn = n;
    for (int i = m - 1; i >= 0; i--) {
        if (r[i] < l_mn) continue;
        l_mn = min(l_mn, l[i]);        
    }

    seg_tree seg;
    seg.build(n);
    seg.set(n, 0);

    for (int i = m - 1; i >= 0; i--) {
        ll res = seg.query(l[i] + 1, r[i]) + 1;
        seg.set(l[i], res);
    }

    cout << seg.query(l_mn, l_mn);
}
