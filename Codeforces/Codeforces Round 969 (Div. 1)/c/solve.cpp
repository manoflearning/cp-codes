#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<ll>>;
#define fr first
#define sc second
#define pb push_back
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}

// what: point update + range sum on a fixed-size array using a tree.
// time: build O(n), update/query O(log n); memory: O(n)
// constraint: 1-indexed [1, n]; a[0] unused.
// usage: seg_tree st; st.build(a); st.set(p, v); st.query(l, r);
struct seg_gcd {
    int flag;
    vl t;
    void build(int n) {
        // goal: build tree from 1-indexed array.
        flag = 1;
        while (flag < n) flag <<= 1;
        t.assign(2 * flag, 0);
    }
    void set(int p, ll val) {
        // goal: set a[p] = val.
        for (t[p += flag - 1] = val; p > 1; p >>= 1)
            t[p >> 1] = gcd(t[p], t[p ^ 1]);
    }
    ll query(int l, int r) const { return query(l, r, 1, 1, flag); }
    ll query(int l, int r, int v, int nl, int nr) const {
        // result: sum on [l, r] within node range.
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[v];
        int mid = (nl + nr) >> 1;
        return gcd(query(l, r, v << 1, nl, mid), query(l, r, v << 1 | 1, mid + 1, nr));
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n; cin >> n;

        vi a(n);
        for (auto &i : a) cin >> i;

        ll ans = (ll)n * (n + 1) / 2;

        vector<pll> b(1, {0, 0});
        for (auto &i : a) {
            if (b.empty() || b.back().fr != i) {
                b.push_back({i, 1});
            } else {
                b.back().sc++;
            }
        }

        seg_gcd seg_g;
        seg_g.build(sz(b));

        vl psum(sz(b));

        for (int i = 1; i < sz(b); i++) {
            if (i + 1 < sz(b))
                seg_g.set(i + 1, abs(b[i + 1].fr - b[i].fr));
            psum[i] = b[i].sc + psum[i - 1];
        }

        int j = 1;
        for (int i = 1; i + 1 < sz(b); i++) {
            while (j < i) j++;
            while (j + 1 < sz(b)) {
                int g = seg_g.query(i + 1, j + 1);
                while (g > 1 && !(g & 1)) g >>= 1;

                if (g == 0 || g > 1) j++;
                else break;
            }

            ll l = psum[j] - psum[i - 1];

            ll res = 0;
            res += b[i].sc * (l - b[i].sc);

            ans -= res;
        }

        cout << ans << '\n';
    }
}
