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
#define rall(x) (x).rbegin(), (x).rend()

constexpr int INF = 1e9 + 7;

// what: range add and range sum with lazy propagation.
// time: update/query O(log n); memory: O(n)
// constraint: 1-indexed [1, n]; a[0] unused.
// usage: seg_tree_lz st; st.build(a); st.add(l, r, v); st.query(l, r);
struct seg_tree_lz {
    int flag;
    vector<ll> t, lz;
    void build(int n) {
        // goal: build tree and clear lazy tags.
        flag = 1;
        while (flag < n) flag <<= 1;
        t.assign(2 * flag, INF);
        for (int i = flag; i < flag + n; i++) {
            t[i] = i - flag + 1;
        }
        for (int i = flag - 1; i >= 1; i--) {
            t[i] = min(t[i << 1], t[i << 1 | 1]);
        }
        lz.assign(2 * flag, 0);
    }
    void add(int l, int r, ll val) { add(l, r, val, 1, 1, flag); }
    ll query(int l, int r) { return query(l, r, 1, 1, flag); }
    void add(int l, int r, ll val, int v, int nl, int nr) {
        // goal: add val to all indices in [l, r].
        push(v, nl, nr);
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            lz[v] += val;
            push(v, nl, nr);
            return;
        }
        int mid = (nl + nr) >> 1;
        add(l, r, val, v << 1, nl, mid);
        add(l, r, val, v << 1 | 1, mid + 1, nr);
        t[v] = min(t[v << 1], t[v << 1 | 1]);
    }
    ll query(int l, int r, int v, int nl, int nr) {
        // result: sum on [l, r].
        push(v, nl, nr);
        if (r < nl || nr < l) return INF;
        if (l <= nl && nr <= r) return t[v];
        int mid = (nl + nr) >> 1;
        return min(query(l, r, v << 1, nl, mid), query(l, r, v << 1 | 1, mid + 1, nr));
    }
    void push(int v, int nl, int nr) {
        // goal: propagate lazy value to children.
        if (lz[v] == INF) return;
        if (v < flag) {
            lz[v << 1] += lz[v];
            lz[v << 1 | 1] += lz[v];
        }
        t[v] += lz[v];
        lz[v] = 0;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];

        vector<int> pmin(n + 2, INF), smin(n + 2, INF);
        for (int i = 1; i <= n; i++) {
            pmin[i] = min(a[i], pmin[i - 1]);
        }
        for (int i = n; i >= 1; i--) {
            smin[i] = min(a[i], smin[i + 1]);
        }

        int ans = 0;

        seg_tree_lz seg;
        seg.build(n);

        for (int i = 1; i <= n; i++) {
            seg.add(smin[i], n, -1);
        }

        for (int i = 1; i <= n; i++) {
            if (1 < i) seg.add(pmin[i - 1], n, -1);
            seg.add(smin[i], n, 1);

            ans += (seg.query(1, n) >= 1);
        }
        cout << ans << '\n';
    }
}
