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

constexpr int INF = 1010101;

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

struct pt {
    ll x, y;
    bool operator<(const pt &rhs) const { return x == rhs.x ? y < rhs.y : x < rhs.x; }
    bool operator==(const pt &rhs) const { return x == rhs.x && y == rhs.y; }
};

struct fraction {
    ll n, d;

    fraction(ll n_ = 0, ll d_ = 1) { set(n_, d_); }
    static ll gcd_ll(ll a, ll b) {
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        while (b) {
            ll t = a % b;
            a = b;
            b = t;
        }
        return a;
    }
    void set(ll n_, ll d_) {
        // goal: normalize sign + reduce
        n = n_;
        d = d_;
        norm();
    }
    void norm() {
        if (d < 0) n = -n, d = -d;
        ll g = gcd_ll(n, d);
        if (g) n /= g, d /= g;
    }

    bool operator==(const fraction &rhs) const { return n == rhs.n && d == rhs.d; }
    // bool operator!=(const fraction &rhs) const { return !(*this == rhs); }
    bool operator<(const fraction &rhs) const {
        return (__int128)n * rhs.d < (__int128)rhs.n * d;
    }
    // bool operator>(const fraction &rhs) const { return rhs < *this; }
    // bool operator<=(const fraction &rhs) const { return !(rhs < *this); }
    // bool operator>=(const fraction &rhs) const { return !(*this < rhs); }
    fraction operator+(const fraction &rhs) const {
        fraction ret;
        ret.n = n * rhs.d + rhs.n * d;
        ret.d = d * rhs.d;
        ret.norm();
        return ret;
    }
    // fraction operator-(const fraction &rhs) const {
    //     fraction ret;
    //     ret.n = n * rhs.d - rhs.n * d;
    //     ret.d = d * rhs.d;
    //     ret.norm();
    //     return ret;
    // }
    fraction operator*(const fraction &rhs) const {
        fraction ret;
        ret.n = n * rhs.n;
        ret.d = d * rhs.d;
        ret.norm();
        return ret;
    }
    // fraction operator/(const fraction &rhs) const {
    //     fraction ret;
    //     ret.n = n * rhs.d;
    //     ret.d = d * rhs.n;
    //     ret.norm();
    //     return ret;
    // }
};

int n;
vector<pt> l, r;
map<pair<fraction, fraction>, vector<int>> mp;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    l.assign(n, {0, 0});
    r.assign(n, {0, 0});
    for (int i = 0; i < n; i++) {
        cin >> l[i].x >> l[i].y;
        cin >> r[i].x >> r[i].y;
        if (r[i] < l[i]) swap(l[i], r[i]);

        fraction sl{};
        if (l[i].x != r[i].x) {
            sl.set(r[i].y - l[i].y, r[i].x - l[i].x);
        } else {
            sl.set(INF, 1);
        }

        fraction ic;
        if (l[i].x != r[i].x && l[i].y != r[i].y) {
            const fraction x{-l[i].x, 1};
            const fraction y{l[i].y, 1};
            ic = sl * x + y;
        } else if (l[i].x == r[i].x) {
            ic.set(l[i].x, 1);
        } else if (l[i].y == r[i].y) {
            ic.set(l[i].y, 1);
        } else {
            assert(0);
        }

        mp[{sl, ic}].push_back(i);
    }

    ll ans = 0;
    for (const auto &[_, idxs] : mp) {
        // DEBUG
        // cout << "slope: " << _.fr.n << "/" << _.fr.d << '\n';
        // cout << "intersect: " << _.sc.n << "/" << _.sc.d << '\n';
        // for (int i : idxs) {
        //     cout << i << ' ';
        // }
        // cout << '\n';

        vector<pt> cc;
        for (int i : idxs) {
            cc.push_back(l[i]);
            cc.push_back(r[i]);
        }

        sort(all(cc));
        cc.erase(unique(all(cc)), cc.end());

        vector<int> lc, rc;
        for (auto &i : idxs) {
            int li = lower_bound(all(cc), l[i]) - cc.begin() + 1;
            int ri = lower_bound(all(cc), r[i]) - cc.begin() + 1;
            lc.push_back(li);
            rc.push_back(ri);
            assert(li < ri);
        }

        vector<int> ord(sz(idxs));
        iota(all(ord), 0);
        sort(all(ord), [&](int i, int j) {
            return (lc[i] ^ lc[j] ? lc[i] > lc[j] : rc[i] > rc[j]);
        });

        seg_tree seg;
        seg.build(sz(cc));

        for (int i : ord) {
            ans += seg.query(lc[i], rc[i] - 1);
            seg.add(lc[i]);
        }
    }

    cout << ans << '\n';
}
