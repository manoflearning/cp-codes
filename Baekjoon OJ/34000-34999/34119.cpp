#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
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

constexpr ll INF = 1e9 + 7;

// what: find k-th element by prefix sum on a frequency array.
// time: update/query O(log n); memory: O(n)
// constraint: 1-indexed [1, n], values >= 0.
// usage: seg_tree_kth st; st.init(n); st.add(p, v); st.kth(k);
struct seg_tree_kth {
    int flag;
    vector<ll> t;
    void init(int n) {
        // goal: allocate tree for size n.
        flag = 1;
        while (flag < n) flag <<= 1;
        t.assign(flag << 1, 0);
        // t[n + flag - 1] = INF;
        // for (int i = flag; i >= 1; i--)
        //     t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void add(int p, ll val) {
        // goal: add val to frequency at p.
        for (t[p += flag - 1] += val; p > 1; p >>= 1)
            t[p >> 1] = t[p] + t[p ^ 1];
    }
    ll kth(ll k, int v = 1) const {
        // result: smallest index with prefix sum >= k.
        assert(t[v] >= k);
        if (v >= flag) return v - flag + 1;
        if (k <= t[v << 1]) return kth(k, v << 1);
        return kth(k - t[v << 1], v << 1 | 1);
    }
    ll query(int l, int r) const { return query(l, r, 1, 1, flag); }
    ll query(int l, int r, int v, int nl, int nr) const {
        // result: sum on [l, r] within node range.
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[v];
        int mid = (nl + nr) >> 1;
        return query(l, r, v << 1, nl, mid) + query(l, r, v << 1 | 1, mid + 1, nr);
    }
};

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
    void add(int p, ll val) {
        for (t[p += flag - 1] += val; p > 1; p >>= 1)
            t[p >> 1] = t[p] + t[p ^ 1];
    }
    ll query(int l, int r) const { return query(l, r, 1, 1, flag); }
    ll query(int l, int r, int v, int nl, int nr) const {
        // result: sum on [l, r] within node range.
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[v];
        int mid = (nl + nr) >> 1;
        return query(l, r, v << 1, nl, mid) + query(l, r, v << 1 | 1, mid + 1, nr);
    }
};

int n, q;
vector<ll> d, cc(1, INF);
struct query {
    ll x, p; int idx;
};
vector<query> qu;
vector<ll> ans;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> q;
    d.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
        cc.push_back(d[i]);
    }
    
    sort(cc.rbegin(), cc.rend());
    cc.erase(unique(all(cc)), cc.end());

    map<ll, int> idx;
    for (int i = 1; i < sz(cc); i++) {
        idx[cc[i]] = i;
    }

    qu.resize(q);
    ans.resize(q);
    for (int i = 0; i < q; i++) {
        cin >> qu[i].x >> qu[i].p;
        qu[i].idx = i;
    }

    sort(all(qu), [](const query &i, const query &j) {
        return i.x < j.x;
    });

    seg_tree_kth seg;
    seg_tree seg2;
    seg.init(sz(cc));
    seg.add(sz(cc), INF);
    seg2.build(sz(cc));

    int j = 1;
    for (const auto &i : qu) {
        while (j <= i.x) {
            seg.add(idx[d[j]], d[j]);
            seg2.add(idx[d[j]], 1);
            j++;
        }

        int kth = seg.kth(i.p);
        // cout << i.x << ' ' << i.p << ' ';
        // cout << kth << ' ' << cc[kth] << '\n';
        if (kth == sz(cc)) ans[i.idx] = -1;
        else {
            ans[i.idx] += seg2.query(1, kth - 1);
            ans[i.idx] += (i.p - seg.query(1, kth - 1) + cc[kth] - 1) / cc[kth]; 
        }
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << '\n';
    }
}
