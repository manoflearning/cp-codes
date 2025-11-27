#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define sz(x) (int)(x).size()

constexpr int N = 101010;
constexpr int X = 2020202;
constexpr int Y = 2020202;
constexpr ld EPS = 1e-9;

struct point { int x, y; };
struct line {
    point p, q;
    int idx;
    bool operator<(const line &rhs) const {
        assert(rhs.q.x <= p.x || rhs.p.x <= q.x);

        int x = -1;
        if (rhs.p.x <= p.x && p.x <= rhs.q.x) x = p.x;
        else x = rhs.p.x;
        auto get_y = [&](ld x, const line &i) -> ld {
            if (i.p.x == i.q.x) return i.p.y;
            ld t = (x - i.p.x) / (i.q.x - i.p.x);
            return i.p.y * (1. - t) + i.q.y * t;
        };

        ld y1 = get_y(x, *this), y2 = get_y(x, rhs);
        return y1 > y2 + EPS;
    }
};

int n;
vector<line> a;

struct lineview {
    int idx;
    bool operator<(const lineview &rhs) const {
        const line &i = a[idx], &j = a[rhs.idx];

        assert(j.q.x <= i.p.x || j.p.x <= i.q.x);

        int x = -1;
        if (j.p.x <= i.p.x && i.p.x <= j.q.x) x = i.p.x;
        else x = j.p.x;

        auto get_y = [](ld x, const line &i) -> ld {
            if (i.p.x == i.q.x) return i.p.y;
            ld t = (x - i.p.x) / (i.q.x - i.p.x);
            return i.p.y * (1. - t) + i.q.y * t;
        };

        ld y1 = get_y(x, i), y2 = get_y(x, j);
        return y1 > y2 + EPS;
    }
};

void input() {
    cin >> n;
    a.resize(n);
    int idxp = 0;
    for (auto &[p, q, idx] : a) {
        cin >> p.x >> p.y >> q.x >> q.y;
        if (p.x > q.x) swap(p, q);
        p.x += 1'000'000, p.y += 1'000'000;
        q.x += 1'000'000, q.y += 1'000'000;
        idx = idxp++;
    }
    int x0; cin >> x0;
    x0 += 1'000'000;
    n++;
    a.push_back(line{point{x0, Y}, point{x0, Y}, idxp++});
}

map<int, vector<int>> in, out;
map<int, vector<int>> d;
int adj[N];

void solve() {
    memset(adj, -1, sizeof(adj));

    for (int i = 0; i < n; i++) {
        if (i < n - 1) {
            in[a[i].p.x].push_back(i);
            out[a[i].q.x].push_back(i);
        }

        d[a[i].p.y < a[i].q.y ? a[i].p.x : a[i].q.x].push_back(i);
    }

    set<lineview> st;
    for (int x = 0; x < X; x++) {
        if (in.count(x))
            for (auto &i : in[x]) st.insert(lineview{i});

        if (d.count(x))
            for (auto &i : d[x]) {
                int y = (x == a[i].p.x ? a[i].p.y : a[i].q.y);
                auto it = st.upper_bound(lineview{i});
                if (it == st.end()) continue;
                adj[i] = it->idx;
            }

        if (out.count(x))
            for (auto &i : out[x]) st.erase(lineview{i});
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    input();

    solve();

    int ans = n - 1;
    while (adj[ans] != -1) {
        ans = adj[ans];
    }
    cout << (a[ans].p.y < a[ans].q.y ? a[ans].p.x : a[ans].q.x) - 1'000'000;
}
