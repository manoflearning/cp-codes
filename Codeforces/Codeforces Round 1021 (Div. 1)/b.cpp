#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second

const int MOD = 1e9 + 7;

int n, m, k;
vector<pii> a;
ll ans = 1;
vector<vector<int>> adj;
vector<bool> vis;

void init() {
    ans = 1;
    adj.clear();
    vis.clear();
}

void input() {
    cin >> n >> m >> k;
    a.resize(k + 1);
    for (auto &[x, y] : a) cin >> x >> y;
}

inline int get_hash(int x, int y) { return x * (m + 1) + y; }

void build_graph() {
    adj.resize((n + 1) * (m + 1));
    vis.resize((n + 1) * (m + 1));

    for (int i = 0; i + 1 <= k; i++) {
        int mdx = abs(a[i].fr - a[i + 1].fr);
        int mdy = abs(a[i].sc - a[i + 1].sc);
        if (mdx + mdy != 2) { ans = 0; return; }

        if (mdx == 1 && mdy == 1) {
            int h1 = get_hash(a[i].fr, a[i + 1].sc);
            int h2 = get_hash(a[i + 1].fr, a[i].sc);
            adj[h1].push_back(h2);
            adj[h2].push_back(h1);
        } else if (mdx == 2) {
            int h = get_hash((a[i].fr + a[i + 1].fr) / 2, a[i].sc);
            adj[h].push_back(h);
        } else if (mdy == 2) {
            int h = get_hash(a[i].fr, (a[i].sc + a[i + 1].sc) / 2);
            adj[h].push_back(h);
        }
    }
}

int cntv = 0, cnte = 0;
bool is_contain_self_loop = 0;
void dfs(int v) {
    vis[v] = 1;
    cntv++;
    for (auto &i : adj[v]) {
        if (v <= i) cnte++;
        if (v == i) is_contain_self_loop = 1;

        if (!vis[i]) dfs(i);
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

        build_graph();

        for (int x = 1; x <= n; x++) {
            for (int y = 1; y <= m; y++) {
                int v = get_hash(x, y);
                if (vis[v]) continue;
                cntv = cnte = 0;
                is_contain_self_loop = 0;
                dfs(v);

                if (cntv < cnte) ans *= 0;
                else if (cntv == cnte) {
                    if (is_contain_self_loop) ans = ans * 1 % MOD;
                    else ans = ans * 2 % MOD;
                } else if (cntv == cnte + 1) {
                    ans = ans * cntv % MOD;
                } else assert(0);
            }
        }

        cout << ans << '\n';
    }
}
