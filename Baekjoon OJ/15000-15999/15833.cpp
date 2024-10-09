#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pli pair<ll, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 10101;
const ll INF = 1e18;

int n, m, k;
vector<pli> adj[MAXN];
pii a[18];

vector<int> cc;
ll dist[37][MAXN];

ll dp[18][1 << 18];

void input() {
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w, v });
        adj[v].push_back({ w, u });
    }
    for (int i = 0; i < k; i++) {
        cin >> a[i].fr >> a[i].sc;
        cc.push_back(a[i].fr);
        cc.push_back(a[i].sc);
    }
    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());
}

void dijkstra(int st) {
    int stc = lower_bound(all(cc), st) - cc.begin();
    assert(cc[stc] == st);

    if (dist[stc][st] != INF) return;

    priority_queue<pli> pq;
    dist[stc][st] = 0;
    pq.push({ -dist[stc][st], st });

    while (!pq.empty()) {
        auto [w, v] = pq.top();
        pq.pop();
        w *= -1;

        if (dist[stc][v] < w) continue;

        for (auto& i : adj[v]) {
            ll nw = w + i.fr;
            int nv = i.sc;
            if (dist[stc][nv] > nw) {
                dist[stc][nv] = nw;
                pq.push({ -dist[stc][nv], nv });
            }
        }
    }
}

ll get_dist(int st, int en) {
    int stc = lower_bound(all(cc), st) - cc.begin();
    assert(cc[stc] == st);
    return dist[stc][en];
}

ll f(int x, int bit) {
    ll& ret = dp[x][bit];
    if (ret != -1) return ret;
    if (bit == (1 << k) - 1) return ret = 0;

    ret = INF;
    for (int i = 0; i < k; i++) {
        if ((1 << i) & bit) continue;
        ll res = 0;
        res += get_dist(a[x].sc, a[i].fr);
        res += get_dist(a[i].fr, a[i].sc);
        res += f(i, bit | (1 << i));
        ret = min(ret, res);
    }

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    for (int i = 0; i < 37; i++) {
        for (int j = 0; j < MAXN; j++) {
            dist[i][j] = INF;
        }
    }

    for (int i = 0; i < k; i++) {
        dijkstra(a[i].fr);
        dijkstra(a[i].sc);
    }

    memset(dp, -1, sizeof(dp));

    ll ans = INF;
    for (int i = 0; i < k; i++) {
        ans = min(ans, get_dist(a[i].fr, a[i].sc) + f(i, 1 << i));
    }

    cout << (ans == INF ? -1 : ans);
}
