#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second

const int MAXN = 101;

int n, m;
int a[MAXN][4];
pii pos[MAXN];

int dfsn[101010], dCnt, sNum[101010], sCnt;
int finished[101010];
vector<int> adj[101010];
stack<int> stk;
pii p[101010];
int ans[101010], res[MAXN];
inline int inv(int x) {
  // negative number -a indicates ¬a.
  return (x > 0) ? 2 * (x - 1) : 2 * (-x - 1) + 1;
}
void twoCnf(int a, int b) {
  // (a ∨ b) iff (¬a → b) iff (¬b → a)
  adj[inv(-a)].push_back(inv(b));
  adj[inv(-b)].push_back(inv(a));
}
void imply(int a, int b) { twoCnf(-a, b); }

inline int Hash(int i, int v) { return i * MAXN + v; }
inline int Hash(int i, int j, int k) {
    return MAXN * MAXN + 5 * 5 * i + 5 * j + k;
}

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i][0] >> a[i][1] >> a[i][2] >> a[i][3];
        a[i][0]--; a[i][1]--;
        a[i][2]--; a[i][3]--;
    }
    
    for (int i = 1; i <= n; i++) {
        int u, v;
        cin >> u >> v;
        pos[i] = {u, v};

        // 개구리 배치 조건
        // 1. 개구리가 배치되어야 하는 장소
        twoCnf(Hash(i, u), Hash(i, v));
        if (u != v) {
            imply(Hash(i, u), -Hash(i, v));
            imply(Hash(i, v), -Hash(i, u));
        }
        // 2. 개구리가 배치되어서는 안되는 장소
        for (int j = 1; j <= n; j++) {
            if (j != u && j != v)
                twoCnf(-Hash(i, j), -Hash(i, j));
        }

        // 주제 흥미도 설정
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 5; k++) {
                if (k == a[i][j]) {
                    imply(Hash(i, u), Hash(u, j, k));
                    imply(Hash(i, v), Hash(v, j, k));
                } else {
                    imply(Hash(i, u), -Hash(u, j, k));
                    imply(Hash(i, v), -Hash(v, j, k));
                }
            }
        }
    }

    // 개구리 중복 방지 조건
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                // 서로 다른 두 개구리가 같은 자리에 위치할 수 없다
                if (i != j) imply(Hash(i, k), -Hash(j, k));
            }
        }
    }
    // 통나무 조건
    for (int i = 0; i < m; i++) {
        int u, v, t;
        cin >> u >> v >> t;
        t--;
        for (int j = 0; j < 5; j++) {
            imply(Hash(u, t, j), Hash(v, t, j));
            imply(Hash(v, t, j), Hash(u, t, j));
        }
    }
}

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
  // determining satisfiability
  int isS = 1;
  for (int v = 0; v < 101010; v += 2) {
    // if x and ¬x is in same scc, then the proposition is not satisfiable
    if (sNum[v] == sNum[v + 1]) {
      isS = 0;
      break;
    }
  }
  return isS;
}
void findValueOfEachVariable() {
  // order of scc is the reverse of the topological sort
  for (int v = 0; v < 101010; v++) {
    p[v] = {sNum[v], v};
  }
  sort(p, p + 101010);
  // determining true/false of each variable
  for (int i = 101010 - 1; i >= 0; i--) {
    int v = p[i].sc;
    if (ans[v / 2 + 1] == -1)
      ans[v / 2 + 1] = (v & 1) ? 1 : 0;
  }
  for (int i = 1; i <= n; i++) {
    auto [u, v] = pos[i];
    assert((u != v && (ans[Hash(i, u)] ^ ans[Hash(i, v)])) || (u == v && ans[Hash(i, u)]));
    if (ans[Hash(i, u)]) res[u] = i;
    if (ans[Hash(i, v)]) res[v] = i;
  }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    memset(dfsn, -1, sizeof(dfsn));
    memset(ans, -1, sizeof(ans));

    input();

    for (int v = 0; v < 101010; v++)
        if (dfsn[v] == -1) dfs(v);

    if (isSatisfiable()) {
        findValueOfEachVariable();
        cout << "YES\n";
        for (int i = 1; i <= n; i++)
            cout << res[i] << ' ';
    } else cout << "NO\n";
}
