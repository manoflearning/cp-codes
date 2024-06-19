#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int N = 1010101, M = 1010101;

int n, m;
vector<int> adj[N], radj[N], nadj[N];
int ind[N], forb[N];
map<pair<int, int>, int> mp;

void input() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        radj[v].push_back(u);
        mp[{ u, v }] = i + 1;
    }
}

bool vis_n[N][2];
bool vis_e[M][2];

void dfs(int v, int bit) {
    vis_n[v][bit] = 1;
    for (auto& i : (bit ? adj[v] : radj[v])) {
        if (!vis_n[i][bit]) dfs(i, bit);
        vis_e[mp[{ min(v, i), max(v, i) }]][bit] = 1;
    }
}

int ans = 0;
void solve() {
    dfs(1, 1); // forward
    dfs(n, 0); // backward

    if (!vis_n[n][1]) {
        cout << 0;
        exit(0);
    }

    for (int i = 1; i <= m; i++) {
        if (vis_e[i][0] && vis_e[i][1]) ans++;
    }
    for (int i = 1; i <= n; i++) {
        if (vis_n[i][0] && vis_n[i][1]) ans--;
    }
    ans += 2;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    solve();

    cout << ans;
}