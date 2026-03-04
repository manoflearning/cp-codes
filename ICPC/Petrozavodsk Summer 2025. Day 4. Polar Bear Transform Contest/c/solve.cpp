#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;

struct Tree {
    int flag;
    vector<ll> t, lazy;
    void init(int n, const vector<pll> &a) {
        for (flag = 1; flag < n; flag <<= 1);
        t.assign(flag << 1, 0);
        lazy.assign(flag << 1, 0);
        for (int i = flag; i < flag + n; i++) {
            t[i] = a[i - flag].second;
        }
        for (int i = flag - 1; i >= 0; i--) {
            t[i] = t[i << 1] + t[i << 1 | 1];
        }
    }
    void prop(int v) {
        if (lazy[v] == 0) return;
        if (v < flag) {
            lazy[v << 1] += lazy[v];
            lazy[v << 1 | 1] += lazy[v];
        }

        if (lazy[v] & 1) t[v] *= -1;
        lazy[v] = 0;
    }
    void mul(int l, int r, int v, int vl, int vr) {
        prop(v);
        if (r < vl || vr < l) return;
        if (l <= vl && vr <= r) {
            lazy[v]++;
            prop(v);
            return;
        }
        const int mid = (vl + vr) >> 1;
        mul(l, r, v << 1, vl, mid);
        mul(l, r, v << 1 | 1, mid + 1, vr);
        t[v] = t[v << 1] + t[v << 1 | 1];
    }
    ll query(int l, int r, int v, int vl, int vr) {
        prop(v);
        if (r < vl || vr < l) return 0;
        if (l <= vl && vr <= r) return t[v];
        const int mid = (vl + vr) >> 1;
        return query(l, r, v << 1, vl, mid) + query(l, r, v << 1 | 1, mid + 1, vr);
    }
    void mul(int l, int r) { mul(l, r, 1, 1, flag); }
    ll query(int l, int r) { return query(l, r, 1, 1, flag); }
};

struct Query {
    int l, r, idx;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int m, n, q;
    cin >> m >> n >> q;

    map<string, pll> mp;
    for (int i = 0; i < m; i++) {
        int p; ll v;
        string d;
        cin >> p >> v >> d;
        p--;
        mp[d] = {p, v};
    }

    vector<pll> a(n);
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        a[i] = mp[s];
    }

    Tree seg;
    seg.init(n, a);

    vector<Query> qu(q);
    for (int i = 0; i < q; i++) {
        cin >> qu[i].l >> qu[i].r;
        qu[i].idx = i;
    }

    sort(all(qu), [](Query i, Query j) {
        return i.r < j.r;
    });

    vector<ll> ans(q);

    int i = 0;

    vector<int> stk;
    for (int r = 0; r < n; r++) {
        while (!stk.empty() && a[stk.back()].first < a[r].first) {
            stk.pop_back();
        }

        if (!stk.empty()) {
            seg.mul(stk.back() + 2, r);
        } else {
            seg.mul(1, r);
        }

        stk.push_back(r);

        while (i < q && r + 1 == qu[i].r) {
            ans[qu[i].idx] = seg.query(qu[i].l, qu[i].r);
            i++;
        }
    }

    for (auto &i : ans) cout << i << '\n';
}
