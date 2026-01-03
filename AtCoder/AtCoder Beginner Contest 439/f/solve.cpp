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

constexpr int MOD = 998'244'353;

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
    void add(int p) {
        // goal: set a[p] = val.
        for (t[p += flag - 1]++; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
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

ll power(ll x, ll y) {
    if (!y) return 1;
    ll res = power(x, y / 2);
    return res * res % MOD * (y & 1 ? x : 1) % MOD;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n; cin >> n;

    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) cin >> p[i];

    const int inv2 = power(2, MOD - 2);

    seg_tree seg;
    seg.build(n);

    vector<ll> ssum(n + 2);
    for (int i = n; i >= 1; i--) {
        ll res = 1;
        res = res * power(2, i) % MOD * seg.query(1, p[i] - 1) % MOD;
        seg.add(p[i]);

        ssum[i] = (res + ssum[i + 1]) % MOD;
    }

    ll ans = 0;

    seg.build(n);
    for (int i = 1; i <= n; i++) {
        ll res = 1;
        res = res * power(inv2, i + 1) % MOD * seg.query(1, p[i] - 1) % MOD;
        seg.add(p[i]);

        ans = (ans + res * ssum[i + 1]) % MOD;
        ans = (ans + res * (ssum[i] - ssum[i + 1]) % MOD * 2) % MOD;
        ans = (ans + MOD) % MOD;
    }

    cout << ans;
}
