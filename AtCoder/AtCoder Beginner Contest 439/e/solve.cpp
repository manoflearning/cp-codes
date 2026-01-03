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
        t.assign(2 * flag, 0);
    }
    void set(int p, ll val) {
        // goal: set a[p] = val.
        p += flag - 1;
        t[p] = max(t[p], val);
        for (; p > 1; p >>= 1)
            t[p >> 1] = max(t[p], t[p ^ 1]);
    }
    ll query(int l, int r) const { return query(l, r, 1, 1, flag); }
    ll query(int l, int r, int v, int nl, int nr) const {
        // result: sum on [l, r] within node range.
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[v];
        int mid = (nl + nr) >> 1;
        return max(query(l, r, v << 1, nl, mid), query(l, r, v << 1 | 1, mid + 1, nr));
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n; cin >> n;

    map<int, vector<int>> mp;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        mp[a].push_back(b);
    }

    vector<int> cc(1, -1);
    for (auto &[_, v] : mp) {
        for (auto &i : v) {
            cc.push_back(i);
        }
    }
    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());
    for (auto &[_, v] : mp) {
        for (auto &i : v) {
            i = lower_bound(all(cc), i) - cc.begin();
        }
    }

    seg_tree seg;
    seg.build(n);
    for (auto &[_, v] : mp) {
        vector<pii> lazy_upd;
        for (auto &i : v) {
            int res = seg.query(1, i - 1) + 1;
            lazy_upd.push_back({i, res});
        }
        for (auto &i : lazy_upd) {
            seg.set(i.fr, i.sc);
        }
    }

    cout << seg.query(1, n);
}
