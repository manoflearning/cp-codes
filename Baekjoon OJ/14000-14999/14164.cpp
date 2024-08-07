#include <bits/stdc++.h>
using namespace std;
#define ll long long

int flag;
struct Seg {
    vector<int> t;
    void build(int N) {
        for (flag = 1; flag < N; flag <<= 1);
        t.resize(flag << 1);
    }
    void init() {
        t.clear();
        t.resize(flag << 1);
    }
    void modify(int p) {
        for (t[p += flag - 1]++; p > 1; p >>= 1)
            t[p >> 1] = t[p] + t[p ^ 1];
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
}seg;

struct Point {
    ll x, y; int idx;
    bool operator<(const Point& rhs) const {
        return (x ^ rhs.x ? x < rhs.x : y < rhs.y);
    }
};

int n;
vector<Point> p;
vector<int> order[303];

int ccw(const Point& a, const Point& b, const Point& c) {
    ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    p.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
        p[i].idx = i;
    }

    // preprocessing
    for (int i = 0; i < n; i++) {
        vector<Point> q;
        for (int j = 0; j < n; j++)
            if (j != i) q.push_back(p[j]);
        
        sort(q.begin(), q.end(), [&](const Point& lhs, const Point& rhs) {
            if ((lhs < p[i]) != (rhs < p[i])) return (lhs < p[i]) > (rhs < p[i]);
            return ccw(p[i], lhs, rhs) < 0;
        });

        order[i].resize(n);
        for (int j = 0; j < q.size(); j++) {
            order[i][q[j].idx] = j + 1;
        }
    }

    // solve
    vector<int> ans(n - 2);
    seg.build(n);
    for (int i = 0; i < n - 2; i++) {
        sort(p.begin() + i, p.end(), [&](const Point& lhs, const Point& rhs) {
            return lhs.x ^ rhs.x ? lhs.x < rhs.x : lhs.y < rhs.y;
        });

        sort(p.begin() + i + 1, p.end(), [&](const Point& lhs, const Point& rhs) {
            return ccw(p[i], lhs, rhs) > 0;
        });

        for (int j = i + 1; j < n; j++) {
            int x = p[j].idx;
            seg.init();
            for (int k = j + 1; k < n; k++) {
                assert(ccw(p[i], p[j], p[k]) > 0);
                int y = p[k].idx;
                ans[seg.query(1, order[x][y] - 1)]++;
                seg.modify(order[x][y]);
            }
        }
    }

    for (auto& i : ans)
        cout << i << '\n';
}