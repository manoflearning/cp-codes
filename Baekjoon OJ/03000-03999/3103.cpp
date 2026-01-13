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

constexpr int MOD = 1e9 + 7;
constexpr int K = 303030;

struct seg_pst {
    struct node {
        int l, r;
        pii val;
    };
    int n;
    vector<node> t;
    vector<int> root;

    void newnd() {
        t.push_back({-1, -1, {0, 0}});
    }
    void build(int n_) {
        // goal: build initial version.
        n = n_;
        t.clear();
        t.reserve(22 * n_ + 1);
        root.clear();
        root.reserve(n_ + 1);
        newnd();
        root.push_back(0);
        build(1, n, root[0]);
    }
    void build(int l, int r, int v) {
        // goal: build node v for range [l, r].
        if (l == r) return;
        newnd();
        t[v].l = sz(t) - 1;
        newnd();
        t[v].r = sz(t) - 1;
        int mid = (l + r) >> 1;
        build(l, mid, t[v].l);
        build(mid + 1, r, t[v].r);
        t[v].val.fr = t[t[v].l].val.fr + t[t[v].r].val.fr;
        t[v].val.sc = (t[t[v].l].val.sc + t[t[v].r].val.sc) % MOD;
    }
    void set(int p, pii val) {
        // goal: create new version with a[p] = val.
        newnd();
        root.push_back(sz(t) - 1);
        set(p, val, 1, n, root[sz(root) - 2], root.back());
    }
    void set(int p, pii val, int l, int r, int v1, int v2) {
        // goal: update along path while sharing unchanged nodes.
        if (p < l || r < p) {
            t[v2] = t[v1];
            return;
        }
        if (l == r) {
            t[v2].val = val;
            return;
        }
        int mid = (l + r) >> 1;
        if (p <= mid) {
            t[v2].r = t[v1].r;
            newnd();
            t[v2].l = sz(t) - 1;
            set(p, val, l, mid, t[v1].l, t[v2].l);
        } else {
            t[v2].l = t[v1].l;
            newnd();
            t[v2].r = sz(t) - 1;
            set(p, val, mid + 1, r, t[v1].r, t[v2].r);
        }
        t[v2].val.fr = t[t[v2].l].val.fr + t[t[v2].r].val.fr;
        t[v2].val.sc = (t[t[v2].l].val.sc + t[t[v2].r].val.sc) % MOD;
    }
    pii query(int l, int r, int v, int nl, int nr) const {
        // result: sum on [l, r] in a specific version.
        if (r < nl || nr < l) return {0, 0};
        if (l <= nl && nr <= r) return t[v].val;
        int mid = (nl + nr) >> 1;

        pii res1 = query(l, r, t[v].l, nl, mid);
        pii res2 = query(l, r, t[v].r, mid + 1, nr);
        return {res1.fr + res2.fr, (res1.sc + res2.sc) % MOD};
    }
    pii query(int l, int r, int ver) const { return query(l, r, root[ver], 1, n); }
};

int k, n;
vector<int> a;
vector<int> fac;

seg_pst seg;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    fac.assign(K, 1);
    for (ll i = 2; i < K; i++)
        fac[i] = i * fac[i - 1] % MOD;

    cin >> k >> n;
    a.assign(k + 1, 0);
    for (int i = 1; i <= k; i++) cin >> a[i];
        
    seg.build(k);
    for (int i = k; i >= 1; i--) {
        seg.set(a[i], {1, fac[k - i]});
    }

    auto rank_naive = [&]() -> ll {
        ll ret = 1;
        for (int i = k; i >= 1; i--) {
            ll cnt = seg.query(1, a[i] - 1, k - i).fr;
            ret = (ret + cnt * fac[k - i]) % MOD;
        }
        return ret;
    };

    const ll rank_base = rank_naive();

    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;

        ll rank = rank_base;

        {
            ll prv = seg.query(1, a[r] - 1, k - r).fr;
            ll now = seg.query(1, a[l] - 1, k - r).fr;
            
            rank = (rank - prv * fac[k - r]) % MOD;
            rank = (rank + now * fac[k - r]) % MOD;
        }
        {
            ll prv = seg.query(1, a[l] - 1, k - l).fr;
            ll now = seg.query(1, a[r] - 1, k - l).fr + (a[l] < a[r] ? 1 : 0);
            
            rank = (rank - prv * fac[k - l]) % MOD;
            rank = (rank + now * fac[k - l]) % MOD;
        }
        {
            const int lb = min(a[l], a[r]) + 1;
            const int ub = max(a[l], a[r]) - 1;

            ll p = 0;
            p += seg.query(lb, ub, k - l).sc;
            p -= seg.query(lb, ub, k - r).sc;
            p %= MOD;

            rank = (rank + p * (a[l] < a[r] ? 1 : -1)) % MOD;
        }

        rank = (rank + MOD) % MOD;

        cout << rank << '\n';
    }
}
