#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include <bits/extc++.h>
typedef long double ld;

constexpr int dy[] = {0, 1, 0, -1};
constexpr int dx[] = {1, 0, -1, 0};

constexpr ll INF = 1e9 + 7;
constexpr ld EPS = 1e-9;

struct PushRelabel {
    struct Edge {
        int dest, back;
        ll f, c;
    };
    vector<vector<Edge>> g;
    vector<ll> ec;
    vector<Edge *> cur;
    vector<vi> hs; vi H;

    PushRelabel(int n) : g(n), ec(n), cur(n), hs(2 * n), H(n) {}

    void addEdge(int s, int t, ll cap, ll rcap = 0) {
        if (s == t) return;
        g[s].push_back({t, sz(g[t]), 0, cap});
        g[t].push_back({s, sz(g[s]) - 1, 0, rcap});
    }

    void addFlow(Edge &e, ll f) {
        Edge &back = g[e.dest][e.back];
        if (!ec[e.dest] && f) hs[H[e.dest]].push_back(e.dest);
        e.f += f; e.c -= f; ec[e.dest] += f;
        back.f -= f; back.c += f; ec[back.dest] -= f;
    }
    ll calc(int s, int t) {
        int v = sz(g); H[s] = v; ec[t] = 1;
        vi co(2*v); co[0] = v - 1;
        rep(i, 0, v) cur[i] = g[i].data();
        for (Edge &e : g[s]) addFlow(e, e.c);

        for (int hi = 0;;) {
            while (hs[hi].empty()) if (!hi--) return -ec[s];
            int u = hs[hi].back(); hs[hi].pop_back();
            while (ec[u] > 0) {
                if (cur[u] == g[u].data() + sz(g[u])) {
                    H[u] = 1e9;
                    for (Edge &e : g[u]) if (e.c && H[u] > H[e.dest] + 1)
                        H[u] = H[e.dest] + 1, cur[u] = &e;
                    if (++co[H[u]], !--co[hi] && hi < v) {
                        rep(i,0,v) if (hi < H[i] && H[i] < v)
                            --co[H[i]], H[i] = v + 1;
                    }
                    hi = H[u];
                } else if (cur[u]->c && H[u] == H[cur[u]->dest] + 1)
                    addFlow(*cur[u], min(ec[u], cur[u]->c));
                else ++cur[u];
            }
        }
    }
    bool leftOfMinCut(int a) { return H[a] >= sz(g); }
};

int b, h, r, c;
vector<string> a;
vector<vector<ld>> lights;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    cin >> b >> h >> r >> c;
    a.assign(r, string());
    for (auto &i : a) cin >> i;

    lights.assign(r, vector<ld>(c, 0));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            const ld s = a[i][j] - '0';
            if (!s) continue;

            for (int p = 0; p < r; p++) {
                for (int q = 0; q < c; q++) {
                    ll dist = 0;
                    dist += abs(p - i) * abs(p - i);
                    dist += abs(q - j) * abs(q - j);
                    dist += h * h;
                    // if (pii{i, j} == pii{p, q}) dist += h * h;
                    // if (pii{i, j} == pii{p, q}) dist = 1;
                    lights[p][q] += s / dist;
                }
            }
        }
    }

    PushRelabel pr(r * c + 2);

    const int st = r * c;
    const int en = r * c + 1;

    for (int y = 0; y < r; y++) {
        for (int x = 0; x < c; x++) {
            const int u = c * y + x;
            const bool bit1 = lights[y][x] + EPS >= b;

            for (int d = 0; d < 2; d++) {
                const int ny = y + dy[d], nx = x + dx[d];
                if (ny < 0 || r <= ny || nx < 0 || c <= nx) continue;

                const int v = c * ny + nx;
                const bool bit2 = lights[ny][nx] + EPS >= b;

                int cost = (bit1 && bit2) ? 43 : 11;

                pr.addEdge(u, v, cost, cost);
            }

            if (y == 0 || y == r - 1 || x == 0 || x == c - 1) {
                assert(bit1);
                pr.addEdge(st, u, 1e6);
            }
            
            if (!bit1) {
                pr.addEdge(u, en, 1e6);
            }
        }
    }

    auto flow = pr.calc(st, en);
    cout << flow << '\n';

    // cout << fixed;
    // cout.precision(1);
    // for (int i = 0; i < r; i++) {
    //     for (int j = 0; j < c; j++) {
    //         cout << lights[i][j] << '\t';
    //     }
    //     cout << '\n';
    // }
}
