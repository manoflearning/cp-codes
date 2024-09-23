#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const double EPS = 1e-7;
const int INF = 1e9 + 7;
const int MAXN = 55;
const int MAXM = 111;

struct Point {
    ll x, y, z;
    bool operator<(const Point& rhs) const {
        if (x ^ rhs.x) return x < rhs.x;
        if (y ^ rhs.y) return y < rhs.y;
        return z < rhs.z;
    }
    bool operator==(const Point& rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }
};
ll dist(const Point& p1, const Point& p2) {
    ll d2 = (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) + (p1.z - p2.z) * (p1.z - p2.z);
    double d = sqrt(d2);
    ll ret = (ll)d;
    if (abs(ret - d) > EPS) ret++;
    return ret;
}

Point st, en;
int n, sti, eni;
vector<tuple<Point, Point, ll, ll>> a;
vector<tuple<int, int, ll, ll>> b;

int m;
vector<Point> p(1, { -INF, -INF, -INF });

struct Edge { ll w, t; int v; };
vector<Edge> adj[MAXM];

vector<ll> upper;

void init() {
    a.clear();
    b.clear();
    p.resize(1);
    for (int i = 1; i <= m; i++) adj[i].clear();
    upper.clear();
}

void input() {
    cin >> st.x >> st.y >> st.z >> en.x >> en.y >> en.z;
    cin >> n;
    for (int i = 0; i < n; i++) {
        Point u, v; ll t, d;
        cin >> u.x >> u.y >> u.z >> v.x >> v.y >> v.z;
        cin >> t >> d;
        a.push_back({ u, v, t, d });
    }
}

void value_compression() {
    p.push_back(st);
    p.push_back(en);
    for (int i = 0; i < n; i++) {
        p.push_back(get<0>(a[i]));
        p.push_back(get<1>(a[i]));
    }

    sort(all(p));
    p.erase(unique(all(p)), p.end());

    sti = lower_bound(all(p), st) - p.begin();
    eni = lower_bound(all(p), en) - p.begin();
    for (int i = 0; i < n; i++) {
        int u = lower_bound(all(p), get<0>(a[i])) - p.begin();
        int v = lower_bound(all(p), get<1>(a[i])) - p.begin();
        b.push_back({ u, v, get<2>(a[i]), get<3>(a[i]) });
    }
    m = sz(p) - 1;
}

void graph_modeling() {
    for (int u = 1; u <= m; u++) {
        for (int v = u + 1; v <= m; v++) {
            adj[u].push_back({ dist(p[u], p[v]), -INF, v });
            adj[v].push_back({ dist(p[u], p[v]), -INF, u });
        }
    }

    for (auto& [u, v, t, d] : b) {
        adj[u].push_back({ d, t, v });
        adj[v].push_back({ d, t, u });
    }
}

bool bellman_ford() {
    upper.resize(m + 1, INF);
    upper[sti] = 0;

    bool updated = 0;
    // for (int cnt = 0; cnt <= m; cnt++) {
    while (1) {
        updated = 0;
        for (int v = 1; v <= m; v++) {
            if (upper[v] == INF) continue;
            for (auto& i : adj[v]) {
                ll nupper = max(upper[v], i.t) + i.w;
                if (upper[i.v] > nupper) {
                    upper[i.v] = nupper;
                    updated = 1;
                }
            }
        }
        if (!updated) break;
    }
    return !updated;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        input();

        value_compression();

        graph_modeling();

        assert(bellman_ford());

        cout << upper[eni] << '\n';
        // for (int i = 1; i <= m; i++) {
        //     cout << p[i].x << ' ' << p[i].y << ' ' << p[i].z << ' ' << upper[i] << '\n';
        // }

        init();
    }
}
