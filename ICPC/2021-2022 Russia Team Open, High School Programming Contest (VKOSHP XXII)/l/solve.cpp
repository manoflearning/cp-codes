#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int MOD = 1e9 + 7;
constexpr int INF = 1e9 + 7;

struct Tree {
    typedef pii T;
    static constexpr T unit = {INF, -1};
    T f(T a, T b) const { return min(a, b); }
    vector<T> s; int n;
    Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
    void update(int pos, T val) {
        for (s[pos += n] = val; pos /= 2;) {
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
        }
    }
    T query(int b, int e) const {
        T ra = unit, rb = unit;
        for (b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) ra = f(ra, s[b++]);
            if (e % 2) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};

ll f(int l, int r, const vector<int> &idx, const vector<ll> &pps, const Tree &seg) {
    if (l + 1 >= r) return 0;

    const int lb = idx[l], ub = idx[r - 1]; // [lb, ub)
    const auto opt = seg.query(lb, ub);
    
    // DEBUG
    // cout << lb << ' ' << ub << ' ' << opt.first << ' ' << opt.second << '\n';

    if (opt.second == -1) {
        ll ret = 0;
        for (int i = l; i < r; i++) {
            const ll psum = pps[i] - (i == 0 ? 0 : pps[i - 1]);
            ret = (ret + (i - l) * psum) % MOD;
            ret = (ret - (r - i - 1) * psum) % MOD;
        }
        return ret;
    }

    const int mid = lower_bound(all(idx), opt.second + 1) - idx.begin();

    const ll lcnt = (mid - 1) - (l - 1);
    const ll rcnt = r - mid;

    assert(lcnt >= 1 && rcnt >= 1);

    ll ret = 0;
    ret = (ret + lcnt * rcnt % MOD * opt.first) % MOD;
    ret = (ret + f(l, mid, idx, pps, seg)) % MOD;
    ret = (ret + f(mid, r, idx, pps, seg)) % MOD;
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n;
    ll k;
    cin >> n >> k;

    vector<ll> x(n), d(n);
    for (int i = 0; i < n; i++) {
        ll a, b;
        cin >> a >> b;
        x[i] = max(a, b);
        d[i] = abs(a - b);
    }

    vector<ll> psum(n + 1), cc;
    cc.push_back(0);
    for (int i = 0; i < n; i++) {
        psum[i + 1] = x[i] + psum[i];
        cc.push_back(psum[i + 1] % k);
    }

    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());

    vector<vector<int>> idxs(sz(cc));
    vector<vector<ll>> pps(sz(cc));
    for (int i = 0; i <= n; i++) {
        const int j = lower_bound(all(cc), psum[i] % k) - cc.begin();
        idxs[j].push_back(i);
        pps[j].push_back(psum[i] % MOD);
        if (sz(pps[j]) >= 2) {
            pps[j][sz(pps[j]) - 1] += pps[j][sz(pps[j]) - 2];
            pps[j][sz(pps[j]) - 1] %= MOD;
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = (ans + i * (psum[i] % MOD)) % MOD;
        ans = (ans - (n - i + 1) * (psum[i - 1] % MOD)) % MOD;
    }
    ans = (ans + MOD) % MOD;

    Tree seg(n);
    for (int i = 0; i < n; i++) {
        if (d[i] % k == 0) continue;
        seg.update(i, {d[i], i});
    }

    for (int i = 0; i < sz(cc); i++) {
        if (sz(idxs[i]) <= 1) continue;
        const ll res = f(0, sz(idxs[i]), idxs[i], pps[i], seg);
        ans = (ans - res) % MOD;
    }
    ans = (ans + MOD) % MOD;

    cout << ans << '\n';
}