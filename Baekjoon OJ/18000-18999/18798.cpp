#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;

int flag;
struct Seg1 {
    vector<int> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1, (1 << 30) - 1);
    }
    void modify(int p, int val) {
        for (t[p += flag - 1] = val; p > 1; p >>= 1)
            t[p >> 1] = t[p] & t[p ^ 1];
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return (1 << 30) - 1;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) & query(l, r, n << 1 | 1, mid + 1, nr);
    }
    int find(int l, int r, int x, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return INF;
        if (l <= nl && nr <= r) {
            if ((t[n] & x) == x) return INF;
            if (nl == nr) return nl;
            int mid = (nl + nr) >> 1;
            if ((t[n << 1] & x) == x) return find(l, r, x, n << 1 | 1, mid + 1, nr);
            else return find(l, r, x, n << 1, nl, mid);
        }
        int mid = (nl + nr) >> 1;
        int ret = find(l, r, x, n << 1, nl, mid);
        if (ret == INF) ret = find(l, r, x, n << 1 | 1, mid + 1, nr);
        return ret;
    }
} seg1;
struct Seg2 {
    vector<int> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void add(int p, int val) {
        for (t[p += flag - 1] += val; p > 1; p >>= 1)
            t[p >> 1] = t[p] + t[p ^ 1];
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
} seg2;

int n, k;
int a[252525];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];

    seg1.build(n);
    seg2.build(n);
    for (int i = 1; i <= n; i++) {
        seg1.modify(i, a[i]);
        if (a[i] == k) seg2.add(i, 1);
    }

    int q; cin >> q;
    while (q--) {
        int op, s, e, x;
        cin >> op >> s >> e;
        if (op == 1) {
            cin >> x;
            for (int i = seg1.find(s, e, x); i <= e; i = seg1.find(i + 1, e, x)) {
                if (a[i] == k) seg2.add(i, -1);
                a[i] |= x;
                seg1.modify(i, a[i]);
                if (a[i] == k) seg2.add(i, 1);
            }
        }
        if (op == 2) {
            cout << seg2.query(s, e) << '\n';
        }
    }
}
