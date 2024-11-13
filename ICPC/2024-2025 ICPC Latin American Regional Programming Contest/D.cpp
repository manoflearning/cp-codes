#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXV = 2020;

int n;
int dfsn[MAXV], dCnt, sNum[MAXV], sCnt;
int finished[MAXV];
vector<int> adj[MAXV];
stack<int> stk;
pii p[MAXV];
int ans[MAXV / 2];

inline int inv(int x) {
  // negative number -a indicates ¬a.
  return (x > 0) ? 2 * (x - 1) : 2 * (-x - 1) + 1;
}
void twoCnf(int a, int b) {
  // (a ∨ b) iff (¬a → b) iff (¬b → a)
  adj[inv(-a)].push_back(inv(b));
  adj[inv(-b)].push_back(inv(a));
}

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        string s; cin >> s;
        for (int j = i + 1; j <= n; j++) {
            if (s[j - 1] == '1') {
                twoCnf(-i, -j);
            }
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
  for (int v = 0; v < 2 * n; v += 2) {
    cout << v << ' ' << sNum[v] << '\n';
    cout << v + 1 << ' ' << sNum[v + 1] << '\n';
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
  for (int v = 0; v < 2 * n; v++) {
    p[v] = {sNum[v], v};
  }
  sort(p, p + 2 * n);
  int ans_cnt = 0;
  // determining true/false of each variable
  for (int i = 2 * n - 1; i >= 0; i--) {
    int v = p[i].sc;
    cout << v << '\n';
    if (ans[v / 2 + 1] == -1) {
      ans[v / 2 + 1] = (v & 1) ? 1 : 0;
      ans_cnt += ans[v / 2 + 1];
    //   if (ans[v / 2 + 1]) cout << v / 2 + 1 << '\n';
    }
  }

  cout << ans_cnt;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    memset(dfsn, -1, sizeof(dfsn));
    memset(ans, -1, sizeof(ans));
    
  // finding scc
  for (int v = 0; v < 2 * n; v++)
    if (dfsn[v] == -1) dfs(v);
  if (isSatisfiable()) {
    findValueOfEachVariable();
  } else assert(0);
}
