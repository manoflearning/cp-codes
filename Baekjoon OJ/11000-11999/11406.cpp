#include <bits/stdc++.h>
using namespace std;

int n, m, st, en;
int c[202][202], f[202][202];
vector<int> adj[202];
int prv[202];

void input() {
    cin >> n >> m;
    st = 0, en = n + m + 1;
    for (int i = 1; i <= n; i++) {
        cin >> c[0][i];
        adj[st].push_back(i);
        adj[i].push_back(st);
    }
    for (int i = 1; i <= m; i++) {
        cin >> c[n + i][en];
        adj[n + i].push_back(en);
        adj[en].push_back(n + i);
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> c[j][n + i];
            adj[j].push_back(n + i);
            adj[n + i].push_back(j);
        }
    }
}

void bfs(int st, int en) {
    memset(prv, -1, sizeof(prv));
    queue<int> q;
    q.push(st);
    prv[st] = 0;
    while (!q.empty() && prv[en] == -1) {
        int now = q.front();
        q.pop();
        for (int next : adj[now]) {
            if (prv[next] == -1 && c[now][next] - f[now][next] > 0) {
                q.push(next);
                prv[next] = now;
            }
        }
    }
}

int flow(int st, int en) {
    int block = 1e9 + 7;
    for (int i = en; i != st; i = prv[i]) {
        block = min(block, c[prv[i]][i] - f[prv[i]][i]);
    }
    for (int i = en; i != st; i = prv[i]) {
        f[prv[i]][i] += block;
        f[i][prv[i]] -= block;
    }
    return block;
}

int maxFlow(int st, int en) {
    int ret = 0;
    while (1) {
        bfs(st, en);
        if (prv[en] == -1) break;
        ret += flow(st, en);
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    cout << maxFlow(st, en);
}