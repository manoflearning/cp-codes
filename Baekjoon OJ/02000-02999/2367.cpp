#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int INF = 1e9 + 7;
const int MAXV = 404;

int N, K, D;
int st = 0, en = 400;
vector<int> adj[MAXV];
int c[MAXV][MAXV], f[MAXV][MAXV];
int level[MAXV], work[MAXV];

void input() {
    cin >> N >> K >> D;
    for (int i = 1; i <= D; i++) {
        int x; cin >> x;
        adj[N + i].push_back(en);
        adj[en].push_back(N + i);
        c[N + i][en] = x;
    }
    for (int cow = 1; cow <= N; cow++) {
        int cnt; cin >> cnt;
        adj[st].push_back(cow);
        adj[cow].push_back(st);
        c[st][cow] = K;
        while (cnt--) {
            int x; cin >> x;
            adj[cow].push_back(N + x);
            adj[N + x].push_back(cow);
            c[cow][N + x] = 1;
        }
    }
}

void bfs() {
    memset(level, -1, sizeof(level));
    level[st] = 0;
    queue<int> q;
    q.push(st);
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        for (int next : adj[now]) {
            if (level[next] == -1 && c[now][next] - f[now][next] > 0) {
                level[next] = level[now] + 1;
                q.push(next);
            }
        }
    }
}

int dfs(int now, int flow) {
    if (now == en) return flow;
    for (int& i = work[now]; i < sz(adj[now]); i++) {
        int next = adj[now][i];
        if (level[next] == level[now] + 1 && c[now][next] - f[now][next] > 0) {
            int df = dfs(next, min(c[now][next] - f[now][next], flow));
            if (df > 0) {
                f[now][next] += df;
                f[next][now] -= df;
                return df;
            }
        }
    }
    return 0;
}

int dinic() {
    int ret = 0;
    while (1) {
        bfs();
        if (level[en] == -1) break;
        memset(work, 0, sizeof(work));
        while (1) {
            int flow = dfs(st, INF);
            if (flow == 0) break;
            ret += flow;
        }
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    int total = dinic();
    cout << total;
}