#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>

const int MAXV = 101010;
const int MAXD = 16;

int n, m;
vector<int> adj[MAXV], t[MAXV];

vector<vector<pii>> bcc;
set<int> aPoint;
set<pii> aEdge;

void input() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

int dfsn[MAXV], out[MAXV], dCnt, dp[MAXV];
stack<pii> stk;

int dfs(int now, int prv) {
    int ret = dfsn[now] = ++dCnt;

    int childCnt = 0;
    for (int next : adj[now]) {
        if (next == prv) continue;

        if (dfsn[now] > dfsn[next]) stk.push({ now, next });

        // back edge
        if (dfsn[next] != -1) {
            ret = min(ret, dfsn[next]);
        }
        // tree edge
        else {
            t[now].push_back(next);
            
            childCnt++;
            int tmp = dfs(next, now);
            ret = min(ret, tmp);

            if (prv != -1 && tmp >= dfsn[now])
                aPoint.insert(now);
            if (tmp > dfsn[now])
                aEdge.insert({ min(now, next), max(now, next) });

            if (tmp >= dfsn[now]) {
                vector<pii> nowBCC;
                while (1) {
                    pii t = stk.top();
                    stk.pop();
                    nowBCC.push_back(t);
                    if (t == make_pair(now, next)) break;
                }
                bcc.push_back(nowBCC);
            }
        }
    }

    if (prv == -1 && childCnt > 1)
        aPoint.insert(now);

    out[now] = dCnt;

    return dp[now] = ret;
}

void getBCC() {
    memset(dfsn, -1, sizeof(dfsn));
    for (int v = 1; v <= n; v++)
        if (dfsn[v] == -1) dfs(v, -1);
}

void treeSorting() {
    for (int v = 1; v <= n; v++) {
        sort(t[v].begin(), t[v].end(), [&](int p1, int p2) {
            return dfsn[p1] < dfsn[p2];
        });
    }        
}

void yes() { cout << "yes\n"; }
void no() { cout << "no\n"; }

void query1() {
    int u, v, g1, g2;
    cin >> u >> v >> g1 >> g2;

    if (u == v) { yes(); return; }

    if (aEdge.count({ min(g1, g2), max(g1, g2) })) {
        // wlog, g1 is child node of g2
        if (dfsn[g1] < dfsn[g2]) swap(g1, g2);

        int isUdesendentOfG = (dfsn[g1] <= dfsn[u] && dfsn[u] <= out[g1]);
        int isVdesendentOfG = (dfsn[g1] <= dfsn[v] && dfsn[v] <= out[g1]);
        if (isUdesendentOfG ^ isVdesendentOfG) no();
        else yes();
    }
    else yes();
}

int bSearch(int g, int v) {
    assert(!t[g].empty());
    int l = 0, r = (int)t[g].size() - 1;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (dfsn[t[g][mid]] <= dfsn[v]) l = mid;
        else r = mid - 1;
    }
    return t[g][l];
}

void query2() {
    int u, v, g;
    cin >> u >> v >> g;

    if (u == v) { yes(); return; }
    if (u == g || v == g) { no(); return; }

    if (aPoint.count(g)) {
        int isUdesendentOfG = (dfsn[g] <= dfsn[u] && dfsn[u] <= out[g]);
        int isVdesendentOfG = (dfsn[g] <= dfsn[v] && dfsn[v] <= out[g]);

        if (isUdesendentOfG && isVdesendentOfG) {
            if (bSearch(g, u) == bSearch(g, v)) yes();
            else no();
        }
        else if (isUdesendentOfG || isVdesendentOfG) {
            if (isVdesendentOfG) swap(u, v);
            // wlog, u is descendent node of g
            if (dp[bSearch(g, u)] < dfsn[g]) yes();
            else no();
        }
        else yes();
    }
    else yes();
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    getBCC();

    treeSorting();

    int q; cin >> q;
    while (q--) {
        int op; cin >> op;
        if (op == 1) query1();
        if (op == 2) query2();
    }
}