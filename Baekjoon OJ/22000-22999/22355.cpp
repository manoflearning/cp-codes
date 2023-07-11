// 최적해는 나중 말뚝 높이를 x라 할 때, x = H_i 중에 존재한다.
#include <bits/stdc++.h>
using namespace std;
#define ll long long

int flag;
/*struct Seg {
    vector<ll> t, lazy;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        lazy.resize(flag << 1);
    }
    void addA(int l, int r, ll val, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);
        if (nr < l || r < nl) return;
        if (l <= nl && nr <= r) {
            int lb = (nl - l + 1), ub = (nr - l + 1);
            lazy[n] += val * (lb + ub) * (nr - nl + 1) / 2;
            propagate(n);
            return;
        }
        int mid = (nl + nr) >> 1;
        addA(l, r, val, n << 1, nl, mid);
        addA(l, r, val, n << 1 | 1, mid + 1, nr);
        t[n] = t[n << 1] + t[n << 1 | 1];
    }
    void addB(int l, int r, ll val, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);
        if (nr < l || r < nl) return;
        if (l <= nl && nr <= r) {
            int lb = (r - nr + 1), ub = (r - nl + 1);
            lazy[n] += val * (lb + ub) * (nr - nl + 1) / 2;
            propagate(n);
            return;
        }
        int mid = (nl + nr) >> 1;
        addA(l, r, val, n << 1, nl, mid);
        addA(l, r, val, n << 1 | 1, mid + 1, nr);
        t[n] = t[n << 1] + t[n << 1 | 1];
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1 , mid + 1, nr);
    }
    void propagate(int n) {
        if (!lazy[n]) return;
        if (n < flag) {
            lazy[n << 1] += lazy[n];
            lazy[n << 1 | 1] += lazy[n];
        }
        t[n] += lazy[n];
        lazy[n] = 0;
    }
}seg;*/

struct SegA {
    vector<ll> t, lzst, lzd;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        lzst.resize(flag << 1);
        lzd.resize(flag << 1);
    }
    void add(int l, int r, ll st, ll d, int n = 1, int nl = 1, int nr = flag) {
        propagate(n, nl, nr);
        if (nr < l || r < nl) return;
        if (l <= nl && nr <= r) {
            lzst[n] += st + d * (nl - l);
            lzd[n] += d;
            propagate(n, nl, nr);
            return;
        }
        int mid = (nl + nr) >> 1;
        add(l, r, st, d, n << 1, nl, mid);
        add(l, r, st, d, n << 1 | 1, mid + 1, nr);
        t[n] = t[n << 1] + t[n << 1 | 1];
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        propagate(n, nl, nr);
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1 , mid + 1, nr);
    }
    void propagate(int n, int nl, int nr) {
        if (!lzst[n] && !lzd[n]) return;
        if (n < flag) {
            lzst[n << 1] += lzst[n];
            lzst[n << 1 | 1] += lzst[n] + (nr - nl + 1) * lzd[n] / 2;
            lzd[n << 1] += lzd[n];
            lzd[n << 1 | 1] += lzd[n];
        }
        t[n] += (2 * lzst[n] + lzd[n] * (nr - nl)) * (nr - nl + 1) / 2;
        lzst[n] = lzd[n] = 0;
    }
}A;

struct SegB {
    vector<ll> t, lzst, lzd;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        lzst.resize(flag << 1);
        lzd.resize(flag << 1);
    }
    void add(int l, int r, ll st, ll d, int n = 1, int nl = 1, int nr = flag) {
        propagate(n, nl, nr);
        if (nr < l || r < nl) return;
        if (l <= nl && nr <= r) {
            lzst[n] += st + d * (r - nr);
            lzd[n] += d;
            propagate(n, nl, nr);
            return;
        }
        int mid = (nl + nr) >> 1;
        add(l, r, st, d, n << 1, nl, mid);
        add(l, r, st, d, n << 1 | 1, mid + 1, nr);
        t[n] = t[n << 1] + t[n << 1 | 1];
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        propagate(n, nl, nr);
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1 , mid + 1, nr);
    }
    void propagate(int n, int nl, int nr) {
        if (!lzst[n] && !lzd[n]) return;
        if (n < flag) {
            lzst[n << 1] += lzst[n] + (nr - nl + 1) * lzd[n] / 2;
            lzst[n << 1 | 1] += lzst[n];
            lzd[n << 1] += lzd[n];
            lzd[n << 1 | 1] += lzd[n];
        }
        t[n] += (2 * lzst[n] + lzd[n] * (nr - nl)) * (nr - nl + 1) / 2;
        lzst[n] = lzd[n] = 0;
    }
}B;

int n, k;
ll h[101010], a[101010], b[101010];

void input() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> h[i];
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
}

ll query(int x) { return A.query(x, x) + B.query(x, x); }
ll ternary() {
    int l = 1, r = 101010;
    while (r - l >= 3) {
        int mid1 = (2 * l + r) / 3;
        int mid2 = (l + 2 * r) / 3;
        ll res1 = query(mid1);
        ll res2 = query(mid2);
        if (res1 >= res2) l = mid1;
        else r = mid2;
    }

    ll ret = 1e18;
    for (int i = l; i <= r; i++)
        ret = min(ret, query(i));
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    A.build(101010);
    B.build(101010);
    for (int i = 1; i <= k; i++) {
        B.add(1, h[i], 0, b[i]);
        A.add(h[i], 101010, 0, a[i]);
    }

    ll ans = ternary();
    
    for (int i = 2; i <= n - k + 1; i++) {
        B.add(1, h[i - 1], 0, -b[i - 1]);
        A.add(h[i - 1], 101010, 0, -a[i - 1]);

        B.add(1, h[i + k - 1], 0, b[i + k - 1]);
        A.add(h[i + k - 1], 101010, 0, a[i + k - 1]);

        ans = min(ans, ternary());
    }

    cout << ans;
}