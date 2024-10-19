#include <bits/stdc++.h>
using namespace std;
#define ll long long

int flag;
struct SegBeats {
    struct Node {
        ll sum, mx1, mx2, mx1_cnt;
        Node operator+(const Node& o) const {
            Node ret;
            if (mx1 == o.mx1) return {sum + o.sum, mx1, max(mx2, o.mx2), mx1_cnt + o.mx1_cnt};
            else if (mx1 < o.mx1) return {sum + o.sum, o.mx1, max(mx1, o.mx2), o.mx1_cnt};
            else if (mx1 > o.mx1) return {sum + o.sum, mx1, max(mx2, o.mx1), mx1_cnt};
            else assert(0);
        }
    };
    vector<Node> t;
    void build(int n, const vector<ll>& a) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1, {0, -1, -1, 0});
        for (int i = flag; i < flag + n; i++)
            t[i] = {a[i - flag + 1], a[i - flag + 1], -1, 1};
        for (int i = flag - 1; i >= 1; i--)
            t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void modify(int l, int r, ll val, int n = 1, int nl = 1, int nr = flag) {
        propagate(n, nl, nr);
        if (r < nl || nr < l || t[n].mx1 <= val) return;
        if (l <= nl && nr <= r && t[n].mx2 < val) {
            t[n].sum -= t[n].mx1_cnt * (t[n].mx1 - val);
            t[n].mx1 = val;
            propagate(n, nl, nr);
            return;
        }
        int mid = (nl + nr) >> 1;
        modify(l, r, val, n << 1, nl, mid);
        modify(l, r, val, n << 1 | 1, mid + 1, nr);
        t[n] = t[n << 1] + t[n << 1 | 1];
    }
    ll get_max(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        propagate(n, nl, nr);
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n].mx1;
        int mid = (nl + nr) >> 1;
        return max(get_max(l, r, n << 1, nl, mid), get_max(l, r, n << 1 | 1, mid + 1, nr));
    }
    ll get_sum(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        propagate(n, nl, nr);
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n].sum;
        int mid = (nl + nr) >> 1;
        return get_sum(l, r, n << 1, nl, mid) + get_sum(l, r, n << 1 | 1, mid + 1, nr);
    }
    void propagate(int n, int nl, int nr) {
        if (nl == nr) return;
        for (auto i : { n << 1, n << 1 | 1 }) {
            if (t[n].mx1 < t[i].mx1) {
                t[i].sum -= t[i].mx1_cnt * (t[i].mx1 - t[n].mx1);
                t[i].mx1 = t[n].mx1;
            }
        }
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
            segb.modify(l, r, x);
        }
        if (op == 2) cout << segb.get_max(l, r) << '\n';
        if (op == 3) cout << segb.get_sum(l, r) << '\n';
    }
}