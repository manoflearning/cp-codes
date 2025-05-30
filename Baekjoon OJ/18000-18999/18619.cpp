#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-8;

int flag;
struct Seg {
    vector<double> t, lazy;
    void build(int N) {
        for (flag = 1; flag < N; flag <<= 1);
        t.resize(flag << 1);
        lazy.resize(flag << 1);
        for (int i = flag; i < flag + N; i++) cin >> t[i];
        for (int i = flag - 1; i >= 1; i--)
            t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void propagate(int n, int nl, int nr) {
        if (lazy[n] < EPS) return;
        if (n < flag) {
            lazy[n << 1] = lazy[n];
            lazy[n << 1 | 1] = lazy[n];
        }
        t[n] = lazy[n] * (nr - nl + 1);
        lazy[n] = 0;
    }
    void modify(int l, int r, double val, int n = 1, int nl = 1, int nr = flag) {
        propagate(n, nl, nr);
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            lazy[n] = val;
            propagate(n, nl, nr);
            return;
        }
        int mid = (nl + nr) >> 1;
        modify(l, r, val, n << 1, nl, mid);
        modify(l, r, val, n << 1 | 1, mid + 1, nr);
        t[n] = t[n << 1] + t[n << 1 | 1];
    }
    double query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        propagate(n, nl, nr);
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
}seg;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    seg.build(n);
    cout << fixed;
    cout.precision(9);
    for (int i = 0; i < m; i++) {
        string op; int x, y;
        cin >> op >> x;
        if (op == "get") {
            cout << seg.query(x, x) << '\n';
        }
        if (op == "shuffle") {
            cin >> y;
            double sum = seg.query(x, y);
            seg.modify(x, y, sum / (y - x + 1));
        }
    }
}