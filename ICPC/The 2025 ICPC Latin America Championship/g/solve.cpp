#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

constexpr ll INF = 4e18;

constexpr char PIPE = '|';
constexpr char HYPHEN = '-';

struct Node {
    ll mn{}, mx{};
    Node operator+(const Node &rhs) const {
        Node ret{};
        ret.mn = min(mn, rhs.mn);
        ret.mx = max(mx, rhs.mx);
        return ret;
    }
};

constexpr Node e{INF, 0};

struct Tree {
    int flag;
    vector<Node> t;
    vector<ll> lazy;

    Tree(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.assign(flag << 1, e);
        lazy.assign(flag << 1, 0);
        for (int i = flag; i < flag + n; i++) t[i] = Node{0, 0};
        for (int i = flag - 1; i >= 1; i--) {
            t[i] = t[i << 1] + t[i << 1 | 1];
        }
    }

    void prop(int n) {
        if (!lazy[n]) return;
        if (n < flag) {
            lazy[n << 1] += lazy[n];
            lazy[n << 1 | 1] += lazy[n];
        }
        t[n].mn += lazy[n], t[n].mx += lazy[n];
        lazy[n] = 0;
    }
    void add(int l, int r, ll val, int n, int nl, int nr) {
        prop(n);
        if (nr < l || r < nl) return;
        if (l <= nl && nr <= r) {
            lazy[n] += val;
            prop(n);
            return;
        }
        const int mid = (nl + nr) >> 1;
        add(l, r, val, n << 1, nl, mid);
        add(l, r, val, n << 1 | 1, mid + 1, nr);
        t[n] = t[n << 1] + t[n << 1 | 1];
    }
    void add(int l, int r, ll val) {
        add(l, r, val, 1, 1, flag);
    }
    Node query(int l, int r, int n, int nl, int nr) {
        prop(n);
        if (nr < l || r < nl) return e;
        if (l <= nl && nr <= r) return t[n];
        const int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);   
    }
    Node query(int l, int r) {
        return query(l, r, 1, 1, flag);
    }
};

struct Piece {
    char op;
    ll l, p;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);

    int n; cin >> n;

    vector<Piece> a(n);
    for (auto &i : a) {
        cin >> i.op >> i.l >> i.p;
        assert(i.op == PIPE || i.op == HYPHEN);
    }

    vector<ll> cc(1, 0);
    for (auto &i : a) {
        cc.push_back(i.p);
        cc.push_back(i.p - 1);
        cc.push_back(i.p + 1);
        cc.push_back(i.p + i.l - 1 - 1);
        cc.push_back(i.p + i.l - 1);
        cc.push_back(i.p + i.l - 1 + 1);
        // if (i.op == HYPHEN) {
        //     cc.push_back(i.p + i.l - 1);   
        // }
    }
    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());

    Tree seg(sz(cc));

    for (auto &i : a) {
        const int xl = lower_bound(all(cc), i.p) - cc.begin();
        const int xr = lower_bound(all(cc), i.p + (i.op == PIPE ? 0 : i.l - 1)) - cc.begin();

        const Node res = seg.query(xl, xr);
        // cout << res.mn << ' ' << res.mx << '\n';
        if (res.mn == res.mx) {
            cout << "S";
            seg.add(xl, xr, i.op == PIPE ? i.l : 1);
        } else {
            cout << "U";
        }
    }
}
