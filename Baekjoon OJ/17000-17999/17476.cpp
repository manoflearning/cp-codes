#include <bits/stdc++.h>
using namespace std;
#define ll long long

int flag;
struct SegBeats {
    struct Node {
        ll sum, mx, mn;
        Node operator+(const Node& o) const {
            return {sum + o.sum, max(mx, o.mx), min(mn, o.mn)};
        }
    };
    vector<Node> t;
    vector<ll> lazy1, lazy2;
    void build(int n, const vector<ll>& a) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1, {0, 0, 0});
        lazy1.resize(flag << 1);
        lazy2.resize(flag << 1);
        for (int i = flag; i < flag + n; i++)
            t[i] = {a[i - flag + 1], a[i - flag + 1], a[i - flag + 1]};
        for (int i = flag - 1; i >= 1; i--)
            t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void add(int l, int r, ll val, int n = 1, int nl = 1, int nr = flag) {
        propagate(n, nl, nr);
        if (nr < l || r < nl) return;
        if (l <= nl && nr <= r) {
            lazy1[n] += val;
            propagate(n, nl, nr);
            return;
        }
        int mid = (nl + nr) >> 1;
        add(l, r, val, n << 1, nl, mid);
        add(l, r, val, n << 1 | 1, mid + 1, nr);
        t[n] = t[n << 1] + t[n << 1 | 1];
    }
    void sq(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        propagate(n, nl, nr);
        if (nr < l || r < nl) return;
        if (l <= nl && nr <= r && (ll)sqrt(t[n].mn) == (ll)sqrt(t[n].mx)) {
            lazy2[n] = (ll)sqrt(t[n].mn);
            propagate(n, nl, nr);
            return;
        }
        if (l <= nl && nr <= r && t[n].mn + 1 == t[n].mx) {
            lazy1[n] = (ll)sqrt(t[n].mn) - t[n].mn;
            propagate(n, nl, nr);
            return;
        }
        int mid = (nl + nr) >> 1;
        sq(l, r, n << 1, nl, mid);
        sq(l, r, n << 1 | 1, mid + 1, nr);
        t[n] = t[n << 1] + t[n << 1 | 1];
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        propagate(n, nl, nr);
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n].sum;
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
    void propagate(int n, int nl, int nr) {
        if (!lazy1[n] && !lazy2[n]) return;
        if (!lazy2[n]) {
            t[n].sum += (nr - nl + 1) * lazy1[n];
            t[n].mx += lazy1[n];
            t[n].mn += lazy1[n];
            if (n < flag) {
                lazy1[n << 1] += lazy1[n];
                lazy1[n << 1 | 1] += lazy1[n];
            }
        } else {
            t[n].sum = (nr - nl + 1) * (lazy1[n] + lazy2[n]);
            t[n].mx = t[n].mn = lazy1[n] + lazy2[n];
            if (n < flag) {
                lazy1[n << 1] = lazy1[n];
                lazy1[n << 1 | 1] = lazy1[n];
                lazy2[n << 1] = lazy2[n];
                lazy2[n << 1 | 1] = lazy2[n];
            }
        }
        lazy1[n] = lazy2[n] = 0;
    }
}segb;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n; cin >> n;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    segb.build(n, a);

    int q; cin >> q;
    while (q--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) {
            int x; cin >> x;
            segb.add(l, r, x);
        }
        if (op == 2) segb.sq(l, r);
        if (op == 3) cout << segb.query(l, r) << '\n';
    }
}