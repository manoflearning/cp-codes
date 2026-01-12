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

struct seg_tree {
    int flag;
    vector<ll> t;
    void build(int n) {
        flag = 1;
        while (flag < n) flag <<= 1;
        t.assign(2 * flag, 0);
    }
    void set(int p, ll val) {
        p += flag - 1;
        t[p] = max(t[p], val);
        for (; p > 1; p >>= 1) {
            t[p >> 1] = max(t[p], t[p ^ 1]);
        }
    }
    ll query(int l, int r) const { return query(l, r, 1, 1, flag); }
    ll query(int l, int r, int v, int nl, int nr) const {
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[v];
        int mid = (nl + nr) >> 1;
        return max(query(l, r, v << 1, nl, mid), query(l, r, v << 1 | 1, mid + 1, nr));
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

        vector<ll> psum(n + 1);
        for (int i = 1; i <= n; i++) {
            psum[i] = v[a[i]] + psum[i - 1];
        }

        ll ans = max(0ll, psum[n]);

        seg_tree seg;
        seg.build(n);
        for (int i = 1; i <= n; i++) {
            ll res = 0;
            // res += psum[i - 1];
            res += max(psum[i - 1], seg.query(1, rb[a[i]])) + v[a[i]];
            ans = max(ans, res);
            seg.set(rb[a[i]], res);
        }
        cout << seg.query(1, n) << '\n';
    }
}