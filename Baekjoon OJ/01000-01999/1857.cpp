#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int dy[] = { 2, 2, -2, -2, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 1, -1, 2, -2, 2, -2 };

inline int Hash(int y, int x) { return 31 * y + x; }

int n, m, st, en;
int arr[33][33];
vector<int> adj[999], dag[999];
vector<int> dist(999, -1);

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 3) st = Hash(i, j);
            if (arr[i][j] == 4) en = Hash(i, j);
        }
    }
}

int vi[33][33];
vector<int> res;

void initDfs() {
    for (int i = 0; i < 33; i++) {
        for (int j = 0; j < 33; j++) {
            vi[i][j] = 0;
        }
    }
    res.clear();
}

void dfs(int y, int x) {
    vi[y][x] = 1;
    if (arr[y][x] == 1) {
        for (int i = 0; i < 8; i++) {
            int ny = y + dy[i], nx = x + dx[i];
            if (ny < 1 || n < ny || nx < 1 || m < nx) continue;
            if (arr[ny][nx] == 2) continue;
            if (vi[ny][nx]) continue;

            dfs(ny, nx);
        }
    }
    else res.push_back(Hash(y, x));
}

void buildGraph() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (arr[i][j] == 2) continue;
            
            initDfs();
            
            vi[i][j] = 1;
            for (int k = 0; k < 8; k++) {
                int y = i + dy[k], x = j + dx[k];
                if (y < 1 || n < y || x < 1 || m < x) continue;
                if (arr[y][x] == 2) continue;

                dfs(y, x);
            }

            for (auto& k : res) 
                adj[Hash(i, j)].push_back(k);
        }
    }
}

int bfs() {    
    queue<int> q;
    q.push(st);
    dist[st] = 0;

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        
        if (v == en) return dist[v];

        for (auto& i : adj[v]) {
            if (dist[i] != -1) continue;
            dist[i] = dist[v] + 1;
            q.push(i);
        }
    }

    return -1;
}

void buildDAG() {
    for (int i = 1; i < 999; i++) {
        for (auto& j : adj[i]) {
            if (dist[j] == dist[i] + 1) 
                dag[i].push_back(j);
        }
    }
}

ll dp[999];

ll f(int v) {
    ll& ret = dp[v];
    if (ret != -1) return ret;
    if (v == en) return ret = 1;

    ret = 0;
    for (auto& i : dag[v])
        ret += f(i);

    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    memset(dp, -1, sizeof(dp));

    input();

    buildGraph();

    int ans = bfs();
    if (ans == -1) {
        cout << -1;
        return 0;
    }

    buildDAG();

    cout << ans - 1 << '\n' << f(st);

    return 0;
}