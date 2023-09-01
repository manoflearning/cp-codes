// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-11;
const bool MAX_BIT = true;
const bool MIN_BIT = false;

int flag;
struct LzSeg {
    vector<double> t, lazy;
    void build(int n) {
        t.clear();
        lazy.clear();
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        lazy.resize(flag << 1);
    }
    void add(int l, int r, double val, bool isMax, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);
        if (nr < l || r < nl) return;
        if (l <= nl && nr <= r) {
            lazy[n] += val;
            propagate(n);
            return;
        }

        int mid = (nl + nr) >> 1;
        add(l, r, val, isMax, n << 1, nl, mid);
        add(l, r, val, isMax, n << 1 | 1, mid + 1, nr);

        if (isMax) t[n] = max(t[n << 1], t[n << 1 | 1]);
        else t[n] = min(t[n << 1], t[n << 1 | 1]);
    }
    double query(int l, int r, bool isMax, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];

        int mid = (nl + nr) >> 1;
        if (isMax) return max(query(l, r, isMax, n << 1, nl, mid), query(l, r, isMax, n << 1 | 1, mid + 1, nr));
        else return min(query(l, r, isMax, n << 1, nl, mid), query(l, r, isMax, n << 1 | 1, mid + 1, nr));
    }
    void propagate(int n) {
        if (lazy[n] < EPS) return;

        if (n < flag) {
            lazy[n << 1] += lazy[n];
            lazy[n << 1 | 1] += lazy[n];
        }
        t[n] += lazy[n];
        lazy[n] = 0;
    }
}mx, mn;

int n;
vector<double> a;

void init() {}

void input() {
    cin >> n;
    a.resize(n + 2);
    a[0] = 0;
    for (int i = 1; i <= n; i++) cin >> a[i];
    a[n + 1] = 1;
}

double unit(int idx) {
    return (double)(idx != 0 && idx != n + 1) / n;
}

double solve() {
    double ret = 0;
    for (int i = 1; i + 1 <= n; i++) {
        ret = max(ret, a[i + 1] - a[i]);
    }

    mx.build(2 * n + 10);
    mn.build(2 * n + 10);

    int idx = 1;

    mx.add(idx, idx, unit(0) - 0, MAX_BIT);
    mn.add(idx, idx, unit(0) - 0, MIN_BIT);
    idx++;

    for (int i = 1; i <= n + 1; i++) {
        // query
        mx.add(1, idx - 1, -(a[i] - a[i - 1]), MAX_BIT);
        mn.add(1, idx - 1, -(a[i] - a[i - 1]), MIN_BIT);

        ret = max(ret, mx.query(1, idx - 1, MAX_BIT));
        ret = max(ret, -mn.query(1, idx - 1, MIN_BIT));

        mx.add(1, idx - 1, unit(i), MAX_BIT);
        mn.add(1, idx - 1, unit(i), MIN_BIT);

        ret = max(ret, mx.query(1, idx - 1, MAX_BIT));
        ret = max(ret, -mn.query(1, idx - 1, MIN_BIT));

        // add new nodes
        mx.add(idx, idx, unit(i) - 0, MAX_BIT);
        mn.add(idx, idx, unit(i) - 0, MIN_BIT);
        idx++;
        mx.add(idx, idx, 0, MAX_BIT);
        mn.add(idx, idx, 0, MIN_BIT);
        idx++;

        // for (int j = i; j <= n; j++) {
        //     ret = max(ret, abs((double)(j - i + 1) / n - (a[j] - a[i])));
        //     ret = max(ret, abs((double)(j - i + 1) / n - (a[j + 1] - a[i])));
        //     ret = max(ret, abs((double)(j - i + 1) / n - (a[j] - a[i - 1])));
        //     ret = max(ret, abs((double)(j - i + 1) / n - (a[j + 1] - a[i - 1])));
        // }
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        cout << "Case #" << tt << '\n';

        init();

        input();

        sort(all(a));

        cout << fixed;
        cout.precision(10);
        cout << solve() << '\n';

        cout << flush;
    }
}