#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 2020, MAXN2 = MAXN * MAXN;
const int dy[] = { -1, 0, 1, 0 };
const int dx[] = { 0, -1, 0, 1 };
const char dir[] = { 'U', 'L', 'D', 'R' };

int n, m, k;
string a[MAXN];
vector<int> adj[MAXN2];

int label[MAXN2], labelCnt;
int SCCnum[MAXN2], SCCcnt, finished[MAXN2];
stack<int> stk;
vector<vector<int>> SCC;

int ans = 0;

void input() {
    cin >> n >> m >> k;
    a[0] = string(m + 2, '*');
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] = '*' + a[i] + '*';
    }
    a[n + 1] = string(m + 2, '*');
}

int ah[MAXN][MAXN];
int Hash(int y, int x) {
    if (y == 0 || y == n + 1) return n * m;
    if (x == 0 || x == m + 1) return n * m;
    return (y - 1) * m + (x - 1);
}

void graph_modeling() {
    for (int i = 0; i <= n + 1; i++) {
        for (int j = 0; j <= m + 1; j++) {
            ah[i][j] = Hash(i, j);
        }
    }
    int edge_cnt = 0;
    for (int y = 1; y <= n; y++) {
        for (int x = 1; x <= m; x++) {
            int d = -1;
            for (int i = 0; i < 4; i++)
                if (a[y][x] == dir[i]) { d = i; break; }
            assert(d != -1);

            for (int i = 1; i <= k; i++) {
                int ny = y + i * dy[d], nx = x + i * dx[d];

                adj[ah[ny][nx]].push_back(ah[y][x]);
                edge_cnt++;

                if (a[ny][nx] == a[y][x]) break;
                if (a[ny][nx] == '*') break;
            }
        }
    }
    assert(edge_cnt <= 4 * (n + 1) * (m + 1));
}

int dfs(int v) {
    label[v] = labelCnt++;
    stk.push(v);
    int ret = label[v];
    for (auto& next : adj[v]) {
        if (label[next] == -1) ret = min(ret, dfs(next));
        else if (!finished[next]) ret = min(ret, label[next]);
    }
    if (ret == label[v]) {
        SCC.resize(sz(SCC) + 1);
        while (1) {
            int t = stk.top();
            stk.pop();
            SCC.back().push_back(t);
            SCCnum[t] = SCCcnt;
            finished[t] = 1;
            if (t == v) break;
        }
        SCCcnt++;
    }
    ans++;
    return ret;
}

void getSCC() {
    memset(label, -1, sizeof(label));
    dfs(n * m);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    graph_modeling();

    getSCC();

    cout << ans - 1;
}
