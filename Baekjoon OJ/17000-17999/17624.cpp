#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5050;
const int MAXB = 5050;
const int INF = 1e9 + 7;

int n, b;
bool is_b[MAXN];
vector<int> adj[MAXN];

int dp1[MAXN][MAXB], dp2[MAXN][MAXB];
int sumb[MAXN];
int lb[MAXB], ub[MAXB];

void init() {
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXB; j++) {
            dp1[i][j] = INF;
            dp2[i][j] = -INF;
        }
        lb[i] = INF, ub[i] = -INF;
    }
}

void input() {
    cin >> n >> b;
    for (int i = 0; i < b; i++) {
        int x; cin >> x;
        is_b[x] = 1;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void dfs(int v, int prv) {
    if (is_b[v]) {
        dp1[v][1] = dp2[v][1] = 1;
        sumb[v]++;
    } else {
        dp1[v][0] = dp2[v][0] = 1;
    }

    for (auto& u : adj[v]) {
        if (u == prv) continue;

        dfs(u, v);

        vector<int> tmp1(sumb[v] + sumb[u] + 1, INF);
        vector<int> tmp2(sumb[v] + sumb[u] + 1, -INF);
        for (int i = 0; i <= sumb[v]; i++) {
            for (int j = 0; j <= sumb[u]; j++) {
                tmp1[i + j] = min(tmp1[i + j], dp1[v][i] + dp1[u][j]);
                tmp2[i + j] = max(tmp2[i + j], dp2[v][i] + dp2[u][j]);
            }
        }

        for (int i = 0; i <= sumb[v] + sumb[u]; i++) {
            dp1[v][i] = min(dp1[v][i], tmp1[i]);
            dp2[v][i] = max(dp2[v][i], tmp2[i]);
        }

        sumb[v] += sumb[u];
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    init();

    input();

    dfs(1, 0);

    for (int v = 1; v <= n; v++) {
        for (int i = 0; i < MAXB; i++) {
            lb[i] = min(lb[i], dp1[v][i]);
            ub[i] = max(ub[i], dp2[v][i]);
        }
    }

    int ans = 0;

    int q; cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        ans += (lb[y] <= x && x <= ub[y]);
    }

    cout << ans;
}
