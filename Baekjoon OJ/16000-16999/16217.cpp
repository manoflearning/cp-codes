#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second

const int MAXN = 303030;

int n, m, k, t;
vector<int> adj[MAXN];
int a[MAXN];

void input() {
    cin >> n >> m >> k >> t;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < k; i++) {
        int x; cin >> x;
        a[x] = 1;
    }
}

vector<vector<pii>> bcc;
set<int> aPoint;
set<pii> aEdge;
int dfsn[MAXN], dCnt;
stack<pii> stk;

int dfs(int now, int prv) {
  int ret = dfsn[now] = ++dCnt;
  int childCnt = 0;
  for (int next : adj[now]) {
    if (next == prv) continue;
    // If an edge { now, next } has not yet been visited, puts an edge on the stack.
    if (dfsn[now] > dfsn[next]) stk.push({now, next});
    // Back edge
    if (dfsn[next] != -1) ret = min(ret, dfsn[next]);
    // Tree edge
    else {
      childCnt++;
      int tmp = dfs(next, now);
      ret = min(ret, tmp);
      if (prv != -1 && tmp >= dfsn[now])
        aPoint.insert(now);
      if (tmp > dfsn[now])
        aEdge.insert({min(now, next), max(now, next)});
      // If next cannot go to ancestor node of now, find BCC
      if (tmp >= dfsn[now]) {
        vector<pii> nowBCC;
        while (true) {
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
  return ret;
}
void getBCC() {
  memset(dfsn, -1, sizeof(dfsn));
  for (int v = 1; v <= n; v++)
    if (dfsn[v] == -1) dfs(v, -1);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    getBCC();

    // for (auto &i : bcc)
    //     for (auto &j : i) cout << j.fr << ' ' << j.sc << '\n';

    for (int v = 1; v <= n; v++) {
        if (aPoint.count(v)) {
            if (a[v]) {

            } else {

            }
        } else {
            if (a[v]) {
                if (k - 1 < t) cout << n - k << ' ';
                else cout << 0 << ' ';
            } else cout << 1 << ' ';
        }
    }
}
