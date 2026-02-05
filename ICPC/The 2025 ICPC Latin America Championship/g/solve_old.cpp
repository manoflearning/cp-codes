#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ll INF = 1e18;

struct Node {
    ll mn{}, mx{};
    Node operator+(const Node &rhs) const {
        Node ret{};
        ret.mn = min(mn, rhs.mn);
        ret.mx = max(mx, rhs.mx);
        return ret;
    }
};

struct Tree {
    int flag;
    vector<Node> t;
    vector<ll> lazy;
    void init(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.assign(flag << 1, Node{INF, 0});
        lazy.assign(flag << 1, 0);
        for (int i = flag; i < flag + n; i++) t[i] = Node{0, 0};
        for (int i = flag - 1; i >= 1; i--)
            t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void prop(int v, int vl, int vr) {
        if (!lazy[v]) return;
        if (v < flag) {
            lazy[v << 1] += lazy[v];
            lazy[v << 1 | 1] += lazy[v];
        }
        t[v].mn += lazy[v], t[v].mx += lazy[v];
        lazy[v] = 0;
    }
    void update(int l, int r, ll val, int v, int vl, int vr) {
        prop(v, vl, vr);
        if (r < vl || vr < l) return;
        if (l <= vl && vr <= r) {
            lazy[v] += val;
            prop(v, vl, vr);
            return;
        }
        const int mid = (vl + vr) >> 1;
        update(l, r, val, v << 1, vl, mid);
        update(l, r, val, v << 1 | 1, mid + 1, vr);
        t[v] = t[v << 1] + t[v << 1 | 1];
    }
    void update(int l, int r, ll val) { update(l, r, val, 1, 1, flag); }
    Node query(int l, int r, int v, int vl, int vr) {
        prop(v, vl, vr);
        if (r < vl || vr < l) return Node{INF, 0};
        if (l <= vl && vr <= r) return t[v];
        const int mid = (vl + vr) >> 1;
        return query(l, r, v << 1, vl, mid) + query(l, r, v << 1 | 1, mid + 1, vr);
    }
    Node query(int l, int r) { return query(l, r, 1, 1, flag); }
};

struct Block {
    char op;
    ll l, p;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    vector<Block> a(n);
    for (auto &i : a) {
        cin >> i.op >> i.l >> i.p;
    }

    vector<ll> cc;
    for (auto &i : a) {
        if (i.op == '|') {
            cc.push_back(i.p);
        } else {
            cc.push_back(i.p);
            cc.push_back(i.p + i.l - 1);
        }
    }
    cc.push_back(-INF);
    
    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());

    // for (auto &i : cc) cout << i << ' ';
    // cout << '\n';

    Tree seg;
    seg.init(sz(cc));

    for (auto &i : a) {
        const int x_l = lower_bound(all(cc), i.p) - cc.begin();
        const int x_r = lower_bound(all(cc), i.p + (i.op == '|' ? 0 : i.l - 1)) - cc.begin();
        // cout << x_l << ' ' << x_r << '\n';
        const auto res = seg.query(x_l, x_r);
        if (res.mn == res.mx) {
            cout << "S";
            seg.update(x_l, x_r, (i.op == '|' ? i.l : 1));
        } else {
            cout << "U";
        }
    }
}
