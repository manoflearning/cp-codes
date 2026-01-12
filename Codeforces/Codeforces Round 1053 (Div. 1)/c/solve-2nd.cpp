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

constexpr ll INF = 1e18;

struct seg_tree_lz {
    int flag;
    vector<ll> t;
    vector<pll> lz;
    void build(int n) {
        flag = 1;
        while (flag < n) flag <<= 1;
        t.assign(2 * flag, -INF);
        for (int i = 1; i < flag + n; i++) t[i] = 0;
        lz.assign(2 * flag, {0, -INF});
    }
    void modify(int l, int r, pll val) { modify(l, r, val, 1, 1, flag); }
    void modify(int l, int r, pll val, int v, int nl, int nr) {
        push(v, nl, nr);
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            lz[v] = val;
            push(v, nl, nr);
            return;
        }
        int mid = (nl + nr) >> 1;
        modify(l, r, val, v << 1, nl, mid);
        modify(l, r, val, v << 1 | 1, mid + 1, nr);
        t[v] = max(t[v << 1], t[v << 1 | 1]);
    }
    ll query(int l, int r) { return query(l, r, 1, 1, flag); }
    ll query(int l, int r, int v, int nl, int nr) {
        push(v, nl, nr);
        if (r < nl || nr < l) return -INF;
        if (l <= nl && nr <= r) return t[v];
        int mid = (nl + nr) >> 1;
        return max(query(l, r, v << 1, nl, mid), query(l, r, v << 1 | 1, mid + 1, nr));
    }
    void push(int v, int nl, int nr) {
        if (lz[v] == pll{0, -INF}) return;
        if (v < flag) {
            lz[v << 1].fr += lz[v].fr;
            lz[v << 1].sc += lz[v].fr;
            lz[v << 1].sc = max(lz[v << 1].sc, lz[v].sc);

            lz[v << 1 | 1].fr += lz[v].fr;
            lz[v << 1 | 1].sc += lz[v].fr;
            lz[v << 1 | 1].sc = max(lz[v << 1 | 1].sc, lz[v].sc);

            // lz[v << 1].fr = max(lz[v << 1].fr, lz[v].sc);
            // lz[v << 1 | 1].fr = max(lz[v << 1 | 1].fr, lz[v].sc);
        }
        t[v] += lz[v].fr;
        t[v] = max(t[v], lz[v].sc);
        lz[v] = {0, -INF};
    } 
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vector<ll> v(n + 1), a(n + 1), b(n + 1), rb(n + 1);
        for (int i = 1; i <= n; i++) cin >> v[i];
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) {
            cin >> b[i];
            rb[b[i]] = i;
        }

        ll ans = 0;

        seg_tree_lz seg;
        seg.build(n + 1);
        for (int i = 1; i <= n; i++) {
            const ll nxt = seg.query(1, rb[a[i]]);
            seg.modify(rb[a[i]] + 1, n + 1, {0, nxt});
            seg.modify(1, rb[a[i]], {v[a[i]], -INF});
        }

        cout << seg.query(1, n + 1) << '\n';
    }
}