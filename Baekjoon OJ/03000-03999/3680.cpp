#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const ll INF = 1e18;
const double EPS = 1e-7;

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
    ll dist(const Point& rhs) const {
        ll d2 = 0;
        d2 += (x - rhs.x) * (x - rhs.x);
        d2 += (y - rhs.y) * (y - rhs.y);
        d2 += (z - rhs.z) * (z - rhs.z);

        double d = sqrt(d2);

        ll ret = (ll)d;
        if (abs(ret - d) > EPS) ret++;
        return ret;
    }
};

struct Wormhole {
    Point u, v;
    int p, q; ll t, d;
};

int n;
Point stp, enp;
int st, en;
vector<Wormhole> wh(MAXN);

int m;
vector<vector<vector<pair<ll, int>>>> adj(2, vector<vector<pair<ll, int>>>(MAXM));
vector<vector<ll>> upper(2, vector<ll>(MAXM, INF));

void init() {}

void input() {
    cin >> stp.x >> stp.y >> stp.z;
    cin >> enp.x >> enp.y >> enp.z;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> wh[i].u.x >> wh[i].u.y >> wh[i].u.z;
        cin >> wh[i].v.x >> wh[i].v.y >> wh[i].v.z;
        cin >> wh[i].t >> wh[i].d;
    }
}

void coordinate_compression() {
    vector<Point> ps;
    ps.push_back({ -INF, -INF, -INF });
    ps.push_back(stp);
    ps.push_back(enp);
    for (int i = 1; i <= n; i++) {
        ps.push_back(wh[i].u);
        ps.push_back(wh[i].v);
    }

    sort(all(ps));
    ps.erase(unique(all(ps)), ps.end());

    st = lower_bound(all(ps), stp) - ps.begin();
    en = lower_bound(all(ps), enp) - ps.begin();

    for (int i = 1; i <= n; i++) {
        wh[i].p = lower_bound(all(ps), wh[i].u) - ps.begin();
        wh[i].q = lower_bound(all(ps), wh[i].v) - ps.begin();
    }

    m = sz(ps) - 1;
}

void graph_modeling() {
    for (int i = 1; i <= n; i++) {
        int p = wh[i].p, q = wh[i].q;
        ll d = wh[i].d;
        Point u = wh[i].u, v = wh[i].v;

        adj[0][p].push_back({ u.dist(v), q });
        adj[0][q].push_back({ u.dist(v), p });

        adj[1][p].push_back({ d, q });
        adj[1][q].push_back({ d, p });

        adj[0][p].push_back({ u.dist(stp), st });
        adj[0][st].push_back({ u.dist(stp), p });
        adj[0][p].push_back({ u.dist(enp), en });
        adj[0][en].push_back({ u.dist(enp), p });

        adj[0][q].push_back({ v.dist(stp), st });
        adj[0][st].push_back({ v.dist(stp), q });
        adj[0][q].push_back({ v.dist(enp), en });
        adj[0][en].push_back({ v.dist(enp), q });
    }
}

bool bellman_ford() {
    upper[0][st] = 0;

    for (int k = 0; k <= 2 * m + 1; k++) {
        for (int v = 1; v <= m; v++) {
            if (upper[0][v] < INF) {
                for (auto& i : adj[0][v]) {
                    
                }
            }
        }
    }
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
        init();
        
        input();

        coordinate_compression();

        graph_modeling();
    }
}