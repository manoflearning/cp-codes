#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 202020;

int n, q;
ll p[N];

int flag;
struct Seg1 {
    vector<pair<ll, int>> t;
    vector<ll> lazy;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        lazy.resize(flag << 1);
        for (int i = flag; i < flag + n; i++) {
            t[i].first = p[i - flag + 1];
            t[i].second = i - flag + 1;
        }
        for (int i = flag + n; i < 2 * flag; i++) {
            t[i].first = 1e18;
        }
        for (int i = flag - 1; i >= 1; i--) {
            t[i] = min(t[i << 1], t[i << 1 | 1]);
        }
    }
    void propagate(int n) {
        if (lazy[n] != 0) {
            if (n < flag) {
                lazy[n << 1] += lazy[n];
                lazy[n << 1 | 1] += lazy[n];
            }
            t[n].first += lazy[n];
            lazy[n] = 0;
        }
    }
    void add(int l, int r, ll w, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            lazy[n] += w;
            propagate(n);
            return;
        }
        int mid = (nl + nr) >> 1;
        add(l, r, w, n << 1, nl, mid);
        add(l, r, w, n << 1 | 1, mid + 1, nr);
        t[n] = min(t[n << 1], t[n << 1 | 1]);
    }
    pair<ll, int> query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);
        if (r < nl || nr < l) return {1e18, 1e9};
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
} seg1;

struct Seg2 {
    struct Node {
        ll w, sum, rng;
        Node operator+(const Node &rhs) const {
            return {w + rhs.w, sum + rhs.sum, rng + rhs.rng};
        }
    };
    vector<Node> t, lazy;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        lazy.resize(flag << 1);
    }
    void propagate(int n) {
        if (lazy[n].w != 0 || lazy[n].sum != 0 || lazy[n].rng != 0) {
            if (n < flag) {
                lazy[n << 1].w += lazy[n].w;
                lazy[n << 1].sum += lazy[n].sum;
                lazy[n << 1].rng += lazy[n].rng;
                lazy[n << 1 | 1].w += lazy[n].w;
                lazy[n << 1 | 1].sum += lazy[n].sum;
                lazy[n << 1 | 1].rng += lazy[n].rng;
            }
            t[n].w += lazy[n].w;
            t[n].sum += lazy[n].sum;
            t[n].sum += t[n].w * lazy[n].rng;
            lazy[n] = {0, 0, 0};
        }
    }
    void add(int l, int r, Node no, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            lazy[n].w += no.w;
            lazy[n].sum += no.sum;
            lazy[n].rng += no.rng;
            propagate(n);
            return;
        }
        int mid = (nl + nr) >> 1;
        add(l, r, no, n << 1, nl, mid);
        add(l, r, no, n << 1 | 1, mid + 1, nr);
        t[n] = t[n << 1] + t[n << 1 | 1];
    }
    Node query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);
        if (r < nl || nr < l) return {0, 0, 0};
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
} seg2;


void input() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> p[i];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    input();
    
    seg1.build(n);
    seg2.build(n);

    while (q--) {
        int op; cin >> op;

        if (op == 1) {
            int l, r, k;
            cin >> l >> r >> k;

            seg1.add(l, r, -k);
            seg2.add(l, r, {0, 0, 1});

            while (1) {
                auto [w, idx] = seg1.query(l, r);                
                // cout << w << ' ' << idx << '\n';
                // break;
                if (w > 0) break;

                p[idx] >>= 1;
                p[idx] = max(p[idx], 1ll);

                seg1.add(idx, idx, -w + (p[idx] == 1 ? (ll)1e18 : p[idx]));
                seg2.add(idx, idx, {(p[idx] == 1 ? 1 : 0), 1, 0});
            }
        } else {
            int l, r;
            cin >> l >> r;

            auto res = seg2.query(l, r);
            cout << res.sum << '\n';
        }
    }
}
