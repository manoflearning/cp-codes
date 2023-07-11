#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXV = 6060;

int n;
struct Point { ll x, y; };
struct Line { Point a, b; };
Line a[MAXV];

void input() {
    cin >> n;
    for (int i = 1; i <= 3 * n; i++) {
        cin >> a[i].a.x >> a[i].a.y;
        cin >> a[i].b.x >> a[i].b.y;
    }
}

ll ccw(const Point& a, const Point& b, const Point& c) {
    ll res = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
    return (res > 0 ? 1 : (res < 0 ? -1 : 0));
}
bool isCross(const Point& a, const Point& b, const Point& c, const Point& d) {
    ll ab = ccw(a, b, c) * ccw(a, b, d);
    ll cd = ccw(c, d, a) * ccw(c, d, b);
    if (ab == 0 && cd == 0) {
        pair<int, int> A = { a.x, a.y }, B = { b.x, b.y };
        pair<int, int> C = { c.x, c.y }, D = { d.x, d.y };
        if (A > B) swap(A, B);
        if (C > D) swap(C, D);
        return (A >= D && C >= B);
    }
    else return (ab <= 0 && cd <= 0);
}

vector<int> adj[MAXV];

inline int inv(int x) {
    return (x > 0) ? 2 * (x - 1) : 2 * (-x - 1) + 1;
}
void twoCnf(int a, int b) {
    adj[inv(-a)].push_back(inv(b));
    adj[inv(-b)].push_back(inv(a));
}
void buildGraph() {
    for (int i = 1; i <= 3 * n; i++) {
        for (int j = i + 1; j <= 3 * n; j++) {
            if (isCross(a[i].a, a[i].b, a[j].a, a[j].b)) {
                twoCnf(i, j);
            }
        }

        if (i % 3 == 1) {
            twoCnf(-i, -(i + 1));
            twoCnf(-(i + 1), -(i + 2));
            twoCnf(-(i + 2), -i);
        }
    }
}

int dfsn[MAXV], dCnt, sNum[MAXV], sCnt;
int finished[MAXV];
stack<int> stk;
pair<int, int> p[MAXV];
int ans[MAXV / 2];

int dfs(int now) {
    int ret = dfsn[now] = ++dCnt;
    stk.push(now);
    for (int next : adj[now]) {
        if (dfsn[next] == -1) ret = min(ret, dfs(next));
        else if (!finished[next]) ret = min(ret, dfsn[next]);
    }
    if (ret >= dfsn[now]) {
        while (1) {
            int t = stk.top();
            stk.pop();
            sNum[t] = sCnt;
            finished[t] = 1;
            if (t == now) break;
        }
        sCnt++;
    }
    return ret;
}

int isSatisfiable() {
    int isS = 1;
    for (int v = 0; v < 2 * 3 * n; v += 2) {
        if (sNum[v] == sNum[v + 1]) {
            isS = 0;
            break;
        }
    }
    return isS;
}

void findValueOfEachVariable() {
    for (int v = 0; v < 2 * 3 * n; v++) {
        p[v] = { sNum[v], v };
    }
    sort(p, p + 2 * 3 * n);
    for (int i = 2 * 3 * n - 1; i >= 0; i--) {
        int v = p[i].second;
        if (ans[v / 2 + 1] == -1)
            ans[v / 2 + 1] = (v & 1) ? 1 : 0;
    }

    vector<int> arr;
    for (int v = 1; v <= 3 * n; v++)
        if (ans[v]) arr.push_back(v);
    
    cout << arr.size() << '\n';
    for (auto& i : arr)
        cout << i << ' ';
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    buildGraph();

    memset(dfsn, -1, sizeof(dfsn));
    memset(ans, -1, sizeof(ans));
    for (int v = 0; v < 2 * 3 * n; v++)
        if (dfsn[v] == -1) dfs(v);

    if (isSatisfiable()) {
        findValueOfEachVariable();
    }
    else cout << -1;
}

// bipartite match
/*int edgeCnt = 0;

void buildGraph() {
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            for (int u = 0; u < 3; u++) {
                for (int v = 0; v < 3; v++) {
                    if (isCross(a[i][u].a, a[i][u].b, a[j][v].a, a[j][v].b)) {
                        adj[3 * i + u].push_back(3 * j + v);
                        adj[3 * j + v].push_back(3 * i + u);
                        edgeCnt++;
                    }
                }
            }
        }

        for (int u = 0; u < 3; u++) {
            adj[3 * i + u].push_back(3 * i + (u + 1) % 3);
            adj[3 * i + (u + 1) % 3].push_back(3 * i + u);
        }
    }

    for (int i = 0; i < MAXV; i++) {
        if (adj[i].empty()) continue;
        cout << i << ' ';
        for (auto& j : adj[i])
            cout << j << ' ';
        cout << '\n';
    }
}

bool dfs(int a) {
    visited[a] = 1;
    for (int b : adj[a]) {
        if (B[b] == -1 || (!visited[B[b]] && dfs(B[b]))) {
            A[a] = b;
            B[b] = a;
            return 1;
        }
    }
    return 0;
}

int bipartiteMatch() {
    memset(A, -1, sizeof(A));
    memset(B, -1, sizeof(B));
    int ret = 0;
    for (int i = 0; i < MAXV; i++) {
        memset(visited, 0, sizeof(visited));
        if (dfs(i)) ret++;
    }
    return ret;
}*/