#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

const int N = 505;
const int INF = 1e9 + 7;
const int V = N * N - N;

int n, w[N][N];

int flaga = 0, flagb = 0;
vector<int> label[N][N];
vector<int> adj[V];
int cnt0 = 0;

int a[V], b[V], dist[V];
bool used[V];

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> w[i][j];
        }
    }
}
void build_graph() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (w[i][j] == 0) {
                label[i][j].push_back(++flaga);
                cnt0++;
            } else if (w[i][j] > 1) {
                int x = w[i][j];
                while (x-- > 1) {
                    label[i][j].push_back(++flagb);
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (w[i][j]) continue;

            int u = label[i][j][0];
            for (int k = 1; k <= n; k++) {
                if (w[i][k] > 1) for (auto &v : label[i][k]) {
                    if (flaga < flagb)
                        adj[u].push_back(v);
                    else adj[v].push_back(u);
                }
                if (w[k][j] > 1) for (auto &v : label[k][j]) {
                    if (flaga < flagb)
                        adj[u].push_back(v);
                    else adj[v].push_back(u);
                }
            }
        }
    }
}

void bfs() {
    queue<int> qu;
    for (int i = (flaga < flagb ? flaga : flagb); i >= 1; i--) {
        if (!used[i]) {
            dist[i] = 0;
            qu.push(i);
        } else {
            dist[i] = INF;
        }
    }
    while (!qu.empty()) {
        int v = qu.front();
        qu.pop();
        for (int u : adj[v]) {
            if (b[u] != -1 && dist[b[u]] == INF) {
                dist[b[u]] = dist[v] + 1;
                qu.push(b[u]);
            }
        }
    }
}
bool dfs(int v) {
    for (int u : adj[v]) {
        if (b[u] == -1 || (dist[b[u]] == dist[v] + 1 && dfs(b[u]))) {
            used[v] = 1;
            a[v] = u;
            b[u] = v;
            return 1;
        }
    }
    return 0;
}

int hopcroft() {
    memset(a, -1, sizeof(a));
    memset(b, -1, sizeof(b));

    int ret = 0;
    while (1) {
        bfs();
        int flow = 0;
        for (int i = (flaga < flagb ? flaga : flagb); i >= 1; i--)
            if (!used[i] && dfs(i)) flow++;
        if (flow == 0) break;
        ret += flow;
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    input();

    build_graph();

    int total = hopcroft();
    // cout << total << '\n';
    cout << 2 * (cnt0 - total) + total;
}
