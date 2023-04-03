#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>

const int INF = 1e9 + 7;

int flag;
struct Seg {
    vector<pii> t;
    vector<int> lazy;
    void build(int n, const vector<int>& a) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        lazy.resize(flag << 1, INF);
        for (int i = flag; i < flag + n; i++) 
            t[i].first = a[i - flag + 1], t[i].second = i - flag + 1;
        for (int i = flag + n; i < 2 * flag; i++)
            t[i].first = INF, t[i].second = -1;
        for (int i = flag - 1; i >= 1; i--)
            t[i] = min(t[i << 1], t[i << 1 | 1]);
    }
    void modify(int l, int r, int val, int n = 1, int nl = 1, int nr = flag) {
        propagate(n, nl, nr);
        if (nr < l || r < nl) return;
        if (l <= nl && nr <= r) {
            lazy[n] = val;
            propagate(n, nl, nr);
            return;
        }

        int mid = (nl + nr) >> 1;
        modify(l, r, val, n << 1, nl, mid);
        modify(l, r, val, n << 1 | 1, mid + 1, nr);
        t[n] = min(t[n << 1], t[n << 1 | 1]);
    }
    pii query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return { INF, INF };
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
    void propagate(int n, int nl, int nr) {
        if (lazy[n] != INF) {
            if (n < flag) {
                lazy[n << 1] = min(lazy[n << 1], lazy[n]);
                lazy[n << 1 | 1] = min(lazy[n << 1 | 1], lazy[n]);
            }
            t[n].first = lazy[n];
            t[n].second = nl;
            lazy[n] = INF;
        }
    }
}seg;

vector<int> uf(1010101, -1);
vector<int> L(1010101), R(1010101);
int find(int x) {
    if (uf[x] < 0) return x;
    return uf[x] = find(uf[x]);
}
void merge(int u, int v) {
    int U = find(u), V = find(v);
    if (U == V) return;
    L[V] = min(L[V], L[U]);
    R[V] = max(R[V], R[U]);
    uf[U] = V;
}

int n, mx;
vector<int> a(1010101);

void init() {
    for (int i = 1; i < 1010101; i++)
        L[i] = R[i] = i;
}

void input() {
    cin >> n;
    a[0] = a[n + 1] = INF;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    init();

    input();

    seg.build(n, a);

    for (int i = 1; i < n; i++) {
        if (a[i] == a[i + 1]) merge(i, i + 1);
        mx = max(mx, a[i]);
    }
    mx = max(mx, a[n]);

    ll ans = 0;

    pii res = seg.query(1, n);
    while (res.first < mx) {
        int v = res.second, w = res.first;
        
        int l = L[find(v)], r = R[find(v)];
        int lw = seg.query(l - 1, l - 1).first;
        int rw = seg.query(r + 1, r + 1).first;
        //cout << v << ' ' << l << ' ' << r << '\n';
        
        if (lw != INF && lw <= rw) {
            ans += lw - w;
            w = lw;
            merge(v, L[find(v)] - 1);
            seg.modify(l, r, lw);
        }
        if (rw != INF && lw >= rw) {
            ans += rw - w;
            merge(v, R[find(v)] + 1);
            seg.modify(l, r, rw);
        }

        res = seg.query(1, n);
    }

    cout << ans;
}