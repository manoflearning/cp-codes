#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr ll INF = 1e18;
constexpr int N = 101;
constexpr int M = 10101;
constexpr int Q = 101010;

int n, m, q;
struct edge {
    int u, v; ll p, h;
    bool operator<(const edge &rhs) const {
        return p < rhs.p;
    }
};
vector<edge> e;

ll adj[N][N];

struct query {
    int op, u; ll h;
};
query qu[Q];

ll dist[N][M];
pll dist2[M];

void input() {
    cin >> n >> m >> q;
    e.resize(m);
    for (auto &i : e) {
        cin >> i.u >> i.v >> i.p >> i.h;
    }
    for (int i = 1; i <= q; i++) {
        cin >> qu[i].op;
        if (qu[i].op == 1) cin >> qu[i].u >> qu[i].h;
        else cin >> qu[i].h;
    }
}

vector<int> cc(1, -1);
void coor_comp() {
    for (auto &i : e) {
        cc.push_back(i.p);
    }
    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());
    for (auto &i : e) {
        i.p = lower_bound(all(cc), i.p) - cc.begin();
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            adj[i][j] = INF;
        }
        adj[i][i] = 0;
    }

    sort(all(e));

    for (int i = 1; i < sz(cc); i++) {
        dist2[i].fr = INF;
    }

    for (int k = 0; k < sz(e); k++) {
        const auto &i = e[k];

        for (int u = 1; u <= n; u++) {
            if (adj[u][i.u] == INF) continue;
            for (int v = 1; v <= n; v++) {
                if (adj[i.v][v] == INF) continue;
                ll ndist = adj[u][i.u] + i.h + adj[i.v][v];
                if (ndist < adj[u][v]) {
                    adj[u][v] = ndist;
                }
            }
        }

        if (k == sz(e) - 1 || i.p != e[k + 1].p) {
            for (int u = 1; u <= n; u++) {
                ll mx = 0;
                for (int v = 1; v <= n; v++) {
                    mx = max(mx, adj[u][v]);
                }
                dist[u][i.p] = mx;
            }

            for (int v = 1; v <= n; v++) {            
                if (dist[v][i.p] < dist2[i.p].fr || (dist[v][i.p] == dist2[i.p].fr && v < dist2[i.p].sc)) {
                    dist2[i.p] = {dist[v][i.p], v};
                }
            }
        }
    }
}

pll ans[Q];

void type1() {
    for (int i = 1; i <= q; i++) {
        if (qu[i].op != 1) continue;

        int l = 1, r = sz(cc);
        while (l < r) {
            int mid = (l + r) >> 1;
            if (dist[qu[i].u][mid] <= qu[i].h) r = mid;
            else l = mid + 1;
        }
        ans[i].fr = (l == sz(cc) ? -1 : cc[l]);
    }
}

void type2() {
    vector<pii> ord;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < sz(cc); j++) {
            ord.push_back({i, j});
        }
    }

    sort(all(ord), [&](pii i, pii j) {
        return dist[i.fr][i.sc] < dist[j.fr][j.sc];
    });

    vector<pii> acc(sz(ord));
    acc[0] = ord[0];
    for (int i = 1; i < sz(ord); i++) {
        acc[i] = acc[i - 1];
        if (ord[i].sc < acc[i].sc || (ord[i].sc == acc[i].sc && ord[i].fr < acc[i].fr)) {
            acc[i] = ord[i];
        }
    }

    pll opt = {INF, INF};
    for (int i = 1; i <= q; i++) {
        if (qu[i].op != 2) continue;

        int l = 0, r = sz(acc) - 1;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (dist[ord[mid].fr][ord[mid].sc] > qu[i].h) r = mid - 1;
            else l = mid;
        }

        if (dist[ord[l].fr][ord[l].sc] <= qu[i].h) ans[i] = {acc[l].fr, cc[acc[l].sc]};
        else ans[i] = {-1, -1};
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    input();

    coor_comp();

    solve();

    type1();
    type2();

    for (int i = 1; i <= q; i++) {
        if (qu[i].op == 1) cout << ans[i].fr << '\n';
        else cout << ans[i].fr << ' ' << ans[i].sc << '\n';
    }
}
