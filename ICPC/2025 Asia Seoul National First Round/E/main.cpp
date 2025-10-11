#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int flag;
struct Seg {
    vector<ll> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void add(int p, ll val) {
        for (t[p += flag - 1] += val; p > 1; p >>= 1) {
            t[p >> 1] = t[p] + t[p ^ 1];
        }
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
} seg;

const int P = 202020;
const int Q = 202020;

int n, p, q;
int w, h;
struct Point {
    int x, y, c;
    bool operator<(const Point &rhs) const {
        return x < rhs.x;
    }
};
Point a[P];
unordered_map<int, vector<Point>> by_c;

struct Query {
    int l, d, a, b, idx;
    bool operator<(const Query &rhs) const {
        return l < rhs.l;
    }
};
Query qry[Q];
ll ans[Q];

void input() {
    cin >> n >> p >> q;
    cin >> w >> h;
    for (int i = 1; i <= p; i++) {
        cin >> a[i].x >> a[i].y >> a[i].c;
        by_c[a[i].c].push_back(a[i]);
    }
    for (int i = 1; i <= q; i++) {
        cin >> qry[i].l >> qry[i].d >> qry[i].a >> qry[i].b;
        qry[i].idx = i;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    input();

    vector<int> ord(q);
    iota(all(ord), 1);
    sort(all(ord), [&](int i, int j) {
        return qry[i].l < qry[j].l;
    });

    seg.build(n);

    vector<vector<Point>> arr;
    for (auto &it : by_c) {
        arr.push_back(it.second);
    }
    sort(all(arr), [&](const vector<Point> &i, const vector<Point> &j) {
        return sz(i) < sz(j);
    });

    for (auto &b : arr) {
        sort(all(b));

        int st = 0, en = 0;
        for (int i : ord) {
            auto &qu = qry[i];

            while (en < sz(b) && b[en].x <= qu.l + w) {
                seg.add(b[en].y, 1);
                en++;
            }
            while (st < en && b[st].x < qu.l) {
                seg.add(b[st].y, -1);
                st++;
            }

            // if (seg.query(1, n) == 0) break;

            int res = seg.query(qu.d, qu.d + h);
            if (qu.a <= res && res <= qu.b) ans[i]++;
        }

        while (st < en) {
            seg.add(b[st++].y, -1);
        }
    }

    for (int i = 1; i <= q; i++)
        cout << ans[i] << '\n';
}
