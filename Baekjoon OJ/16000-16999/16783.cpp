#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int INF = 1e9 + 7;

int flag;
struct Seg {
    struct Node {
        ll l, r, mx, all;
        Node operator+(const Node& rhs) const {
            Node ret;
            ret.l = max(l, all + rhs.l);
            ret.r = max(rhs.r, r + rhs.all);
            ret.mx = max({ mx, rhs.mx, r + rhs.l });
            ret.all = all + rhs.all;
            return ret;
        }
    };
    vector<Node> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        for (int i = flag; i < flag + n; i++) {
            t[i].l = t[i].r = t[i].mx = 0;
            t[i].all -INF;
        }
        for (int i = flag - 1; i >= 1; i--) {
            t[i] = t[i << 1] + t[i << 1 | 1];
        }
    }
    void modify(int p, ll val) {
        p += flag - 1;
        t[p].l = t[p].r = t[p].mx = max(0ll, val);
        t[p].all = val;
        for (; p > 1; p >>= 1) {
            if (p & 1) t[p >> 1] = t[p ^ 1] + t[p];
            else t[p >> 1] = t[p] + t[p ^ 1];
        }
    }
    ll query() { return t[1].mx; }
}seg;

struct Point {
    ll x, y, w;
    bool operator<(const Point& rhs) const {
        return tie(x, y) < tie(rhs.x, rhs.y);
    }
};

struct Line {
    int u, v; ll dx, dy; // u < v, dx >= 0;
    bool operator<(const Line& rhs) const {
        if (dy * rhs.dx != rhs.dy * dx) return dy * rhs.dx < rhs.dy * dx;
        return tie(u, v) < tie(rhs.u, rhs.v);
    }
    bool operator==(const Line& rhs) const {
        return dy * rhs.dx == rhs.dy * dx;
    }
};

int n, pos[2020];
Point p[2020];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> p[i].x >> p[i].y >> p[i].w;

    sort(p + 1, p + 1 + n);
    seg.build(n);
    for (int i = 1; i <= n; i++) {
        pos[i] = i;
        seg.modify(i, p[i].w);
    }

    vector<Line> arr;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            arr.push_back({ i, j, p[j].x - p[i].x, p[j].y - p[i].y });
        }
    }
    sort(arr.begin(), arr.end());

    ll ans = seg.query();
    for (int i = 0, j = 0; i < arr.size(); i = j) {
        while (j < arr.size() && arr[j] == arr[i]) j++; // all lines in [i, j) are same
        for (int k = i; k < j; k++) {
            int u = arr[k].u, v = arr[k].v;
            swap(p[pos[u]], p[pos[v]]);
            swap(pos[u], pos[v]);
            seg.modify(pos[u], p[pos[u]].w);
            seg.modify(pos[v], p[pos[v]].w);
        }
        ans = max(ans, seg.query());
    }

    cout << ans;
}