#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAXX = 500'000;

struct PST { // 1-indexed
    int flag; // array size
    struct Node { int l, r; ll val; };
    vector<Node> t;
    vector<int> root;
    vector<int> hei;

    void addNode() {
        t.push_back({ -1, -1, 0 });
        hei.push_back(-1);
    }
    void build(int l, int r, int n)  {
        assert(0 <= n && n < sz(t));
        if (l == r) return;
        addNode();
        t[n].l = sz(t) - 1;
        addNode();
        t[n].r = sz(t) - 1;

        int mid = (l + r) >> 1;
        build(l, mid, t[n].l);
        build(mid + 1, r, t[n].r);
        t[n].val = t[t[n].l].val + t[t[n].r].val;
        hei[n] = hei[t[n].l] + 1;
    }
    void build(int Flag) {
        addNode();
        root.push_back(sz(t) - 1);
        for (flag = 1; flag < Flag; flag <<= 1);
        build(0, flag - 1, root[0]);
    }
    void add(int p, int l, int r, int n1, int n2) {
        assert(0 <= n1 && n1 < sz(t));
        assert(0 <= n2 && n2 < sz(t));
        if (p < l || r < p) { t[n2] = t[n1]; return; }
        if (l == r) { t[n2].val = t[n1].val + 1; return; }

        int mid = (l + r) >> 1;
        if (p <= mid) {
            t[n2].r = t[n1].r;
            addNode();
            t[n2].l = sz(t) - 1;
            add(p, l, mid, t[n1].l, t[n2].l);
        }
        else {
            t[n2].l = t[n1].l;
            addNode();
            t[n2].r = sz(t) - 1;
            add(p, mid + 1, r, t[n1].r, t[n2].r);
        }
        t[n2].val = t[t[n2].l].val + t[t[n2].r].val;
        hei[n2] = hei[t[n2].l] + 1;
    }
    void add(int p) {
        addNode();
        root.push_back(sz(t) - 1);
        add(p, 0, flag - 1, root[sz(root) - 2], root[sz(root) - 1]);
    }
    void del() {
        while (root.back() < sz(t)) {
            t.pop_back();
            hei.pop_back();
        }
        root.pop_back();
    }
    int _query2(int x, int l, int r, int n1, int n2) {
        assert(0 <= n1 && n1 < sz(t));
        assert(0 <= n2 && n2 < sz(t));

        if (l == r) return l;
        
        int mid = (l + r) >> 1;
        int bit = (x & (1 << hei[n2]));
        if (bit) {
            if (t[t[n2].l].val - t[t[n1].l].val > 0) {
                return _query2(x, l, mid, t[n1].l, t[n2].l);
            } else {
                return _query2(x, mid + 1, r, t[n1].r, t[n2].r);
            }
        } else {
            if (t[t[n2].r].val - t[t[n1].r].val > 0) {
                return _query2(x, mid + 1, r, t[n1].r, t[n2].r);
            } else {
                return _query2(x, l, mid, t[n1].l, t[n2].l);
            }
        }
    }
    int query2(int x, int n1, int n2) {
        return _query2(x, 0, flag - 1, root[n1], root[n2]);
    }
    ll _query4(int l, int r, int n1, int n2, int nl, int nr) {
        assert(0 <= n1 && n1 < sz(t));
        assert(0 <= n2 && n2 < sz(t));

        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[n2].val - t[n1].val;
        int mid = (nl + nr) >> 1;
        return _query4(l, r, t[n1].l, t[n2].l, nl, mid) + _query4(l, r, t[n1].r, t[n2].r, mid + 1, nr);
    }
    ll query4(int x, int n1, int n2) {
        return _query4(1, x, root[n1], root[n2], 0, flag - 1);
    }
    int _query5(int k, int l, int r, int n1, int n2) {
        assert(0 <= n1 && n1 < sz(t));
        assert(0 <= n2 && n2 < sz(t));

        if (l == r) return l;
        int mid = (l + r) >> 1;
        int lcnt = t[t[n2].l].val - t[t[n1].l].val;
        if (lcnt >= k) return _query5(k, l, mid, t[n1].l, t[n2].l);
        else return _query5(k - lcnt, mid + 1, r, t[n1].r, t[n2].r);
    }
    int query5(int k, int n1, int n2) {
        return _query5(k, 0, flag - 1, root[n1], root[n2]);
    }
}pst;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    pst.build(MAXX);

    int m; cin >> m;
    while (m--) {
        int op; cin >> op;

        if (op == 1) {
            int x; cin >> x;
            pst.add(x);
        } else if (op == 2) {
            int l, r, x;
            cin >> l >> r >> x;
            cout << pst.query2(x, l - 1, r) << '\n';
        } else if (op == 3) {
            int k; cin >> k;
            while (k--) pst.del();
        } else if (op == 4) {
            int l, r, x;
            cin >> l >> r >> x;
            cout << pst.query4(x, l - 1, r) << '\n';
        } else if (op == 5) {
            int l, r, k;
            cin >> l >> r >> k;
            cout << pst.query5(k, l - 1, r) << '\n';
        }
    }
}