#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr int MOD = 1e9 + 7;

ll modpow(ll b, ll e) {
    if (!e) return 1;
    const ll res = modpow(b, e / 2);
    return res * res % MOD * (e & 1 ? b : 1) % MOD;
}

struct Tree {
    int flag;
    vector<ll> t, lazy;
    vector<ll> powc, ps; // ps[i] = c^0 + c^1 + ... + c^i

    Tree(int n, const ll c) {
        for (flag = 1; flag < n; flag <<= 1);
        t.assign(flag << 1, 0);
        lazy.assign(flag << 1, 0);
        
        powc.assign(flag + 1, 0);
        ps.assign(flag + 1, 0);
        powc[0] = ps[0] = 1;
        for (int i = 1; i <= flag; i++) {
            powc[i] = c * powc[i - 1] % MOD;
            ps[i] = (powc[i] + ps[i - 1]) % MOD;
        }
    }
    void prop(int v, int vl, int vr) {
        if (!lazy[v]) return;
        if (v < flag) {
            lazy[v << 1] = (lazy[v << 1] + lazy[v]) % MOD;
            lazy[v << 1 | 1] = (lazy[v << 1 | 1] + lazy[v] * powc[(vr - vl + 1) / 2]) % MOD;
        }
        t[v] = (t[v] + lazy[v] * ps[vr - vl]) % MOD;
        lazy[v] = 0;
    }
    void add(int l, int r, ll val, int v, int vl, int vr) {
        prop(v, vl, vr);
        if (vr < l || r < vl) return;
        if (l <= vl && vr <= r) {
            lazy[v] = val * powc[vl - l] % MOD;
            prop(v, vl, vr);
            return;
        }

        const int mid = (vl + vr) >> 1;
        add(l, r, val, v << 1, vl, mid);
        add(l, r, val, v << 1 | 1, mid + 1, vr);
        t[v] = (t[v << 1] + t[v << 1 | 1]) % MOD;
    }
    void add(int l, int r, ll val) { add(l, r, val, 1, 1, flag); }
    ll query(int l, int r, int v, int vl, int vr) {
        prop(v, vl, vr);
        if (vr < l || r < vl) return 0;
        if (l <= vl && vr <= r) return t[v];
        const int mid = (vl + vr) >> 1;
        return (query(l, r, v << 1, vl, mid) + query(l, r, v << 1 | 1, mid + 1, vr)) % MOD;
    }
    ll query(int l, int r) { return query(l, r, 1, 1, flag); }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, q;
    string _p;
    cin >> n >> q >> _p;

    ll p{};
    {
        int j{-1};
        for (int i = 0; i < sz(_p); i++) {
            if (_p[i] == '.') { j = i; break; }
        }
        assert(j != -1);

        string tmp = _p.substr(j + 1, sz(_p) - j - 1);
        p = stoll(tmp) * modpow(modpow(10, sz(_p) - j - 1), MOD - 2) % MOD;
    }

    const ll c = (1 - p + MOD) % MOD;

    Tree seg1(n, c), seg2(n, c);

    while (q--) {
        char op; cin >> op;

        if (op == '+' || op == '-') {
            ll b; int x;
            cin >> b >> x;

            if (op == '-') b = MOD - b;

            seg1.add(x, n, b);
            seg2.add(n - x + 2, n, b * c % MOD);
        } else {
            assert(op == '?');

            int x; cin >> x;

            int ans = 0;
            ans = (ans + seg1.query(x, x)) % MOD;
            ans = (ans + seg2.query(n - x + 1, n - x + 1)) % MOD;
            cout << ans << '\n';
        }
    }
}
