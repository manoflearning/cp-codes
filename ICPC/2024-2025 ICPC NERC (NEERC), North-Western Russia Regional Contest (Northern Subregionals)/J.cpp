#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const ll INF = 1e18;

const int MAXN = 101010;

int n, m;
vector<pii> e;
set<pii> st;
int outd[MAXN];
vector<int> adj[MAXN];
bool vis[MAXN];

void init() {
    e.clear();
    st.clear();
    for (int i = 1; i <= n; i++) {
        outd[i] = 0;
        adj[i].clear();
        vis[i] = 0;
    }
}

void input() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        e.push_back({u, v});
        st.insert({u, v});
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

        for (auto [u, v] : e) {
            // if (!st.count({v, u})) {
                outd[u]++;
                adj[u].push_back(v);
            // }
        }

        priority_queue<pair<ll, int>> pq;
        for (int v = 1; v <= n; v++) {
            pq.push({outd[v], v});
        }

        vector<int> ans, ord(n + 1);
        while (!pq.empty()) {
            auto [w, v] = pq.top();
            pq.pop();

            outd[v] = 0;
            for (auto i : adj[v]) {
                if (!vis[i]) outd[v]++;
            }

            if (w != outd[v]) {
                pq.push({outd[v], v});
                continue;
            }

            assert(!vis[v]);

            ans.push_back(v);
            ord[v] = sz(ans);
            vis[v] = 1;
        }

        assert(sz(ans) == n);

        int res = 0;
        for (auto &[u, v] : e) {
            if (ord[u] < ord[v]) res++;
        }

        if (res >= (m + 1) / 2) {
            for (auto &i : ans) cout << i << ' ';
            cout << '\n';
        } else cout << -1 << '\n';
    }
}
