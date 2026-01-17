#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct node {
    int up{}, down{};
    ll mx{};
    node operator+(const node &rhs) const {
        node ret{};
        ret.up = up + rhs.up;
        ret.down = down + rhs.down;
        ret.mx = max(mx, rhs.mx);
        return ret;
    }
};
constexpr node unit = {0, 0, 0};

struct seg_tree_lz {
    int flag;
    vector<node> t;
    vector<pair<ll, ll>> lz; // {n_takoyaki, n_flip}
    void init(int n) {
        // goal: allocate tree and clear lazy tags (all zeros).
        flag = 1;
        while (flag < n) flag <<= 1;
        t.assign(2 * flag, {1, 0, 0});
        lz.assign(2 * flag, {0, 0});
    }
    void add(int l, int r, pair<ll, ll> val) { add(l, r, val, 1, 1, flag); }
    void add(int l, int r, pair<ll, ll> val, int v, int nl, int nr) {
        // goal: add val to all indices in [l, r].
        push(v, nl, nr);
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            lz[v] = val;
            push(v, nl, nr);
            return;
        }
        int mid = (nl + nr) >> 1;
        add(l, r, val, v << 1, nl, mid);
        add(l, r, val, v << 1 | 1, mid + 1, nr);
        t[v] = t[v << 1] + t[v << 1 | 1];
    }
    node query(int l, int r) { return query(l, r, 1, 1, flag); }
    node query(int l, int r, int v, int nl, int nr) {
        // result: sum on [l, r].
        push(v, nl, nr);
        if (r < nl || nr < l) return unit;
        if (l <= nl && nr <= r) return t[v];
        int mid = (nl + nr) >> 1;
        return query(l, r, v << 1, nl, mid) + query(l, r, v << 1 | 1, mid + 1, nr);
    }
    void push(int v, int nl, int nr) {
        // goal: propagate lazy value to children.
        if (lz[v] == pair<ll, ll>{0, 0}) return;

        if (v < flag) {
            if (lz[v].second) {
                lz[v << 1].first = 0;
                lz[v << 1 | 1].first = 0;
                lz[v << 1].second += lz[v].second;
                lz[v << 1 | 1].second += lz[v].second;
            }
            lz[v << 1].first += lz[v].first;
            lz[v << 1 | 1].first += lz[v].first;
        }

        if (lz[v].second) {
            t[v].mx = 0;
            if (lz[v].second & 1) {
                swap(t[v].up, t[v].down);
            }
        }
        t[v].mx += (t[v].up > 0 ? lz[v].first : 0);

        lz[v] = {0, 0};
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n, q;
    cin >> n >> q;

    seg_tree_lz seg;
    seg.init(n);

    while (q--) {
        int op, l, r;
        cin >> op >> l >> r;

        if (op == 1) {
            ll x; cin >> x;
            seg.add(l, r, {x, 0});
        } else if (op == 2) {
            seg.add(l, r, {0, 1});
        } else if (op == 3) {
            cout << seg.query(l, r).mx << '\n';
        } else assert(0);
    }
}
