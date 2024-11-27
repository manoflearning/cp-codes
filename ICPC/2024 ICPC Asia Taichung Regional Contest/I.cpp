#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int MAXN = 2020202;
const int ST = 33;
const int MAXC = 126 - 33 + 1;

struct Trie {
  int cnt, t[MAXN][MAXC], par[MAXN];
  priority_queue<int, vector<int>, greater<int>> pq[MAXN];
  bool is_del[MAXN];

  void init() {
    par[0] = -1;
  }
  void add(string &s, int id) {
    int here = 0;
    for (char &i : s) {
      if (!t[here][i - ST]) {
        t[here][i - ST] = ++cnt;
        par[cnt] = here;
      }
      pq[here].push(id);
      here = t[here][i - ST];
    }
  }
  int append(string &s, int here) {
    for (char &i : s) {
      if (!t[here][i - ST]) {
        t[here][i - ST] = ++cnt;
        par[cnt] = here;
      }
      here = t[here][i - ST];
    }
    return here;
  }
  int backspace(int x, int here) {
    while (x--) {
      assert(par[here] != -1);
      here = par[here];
    }
    return here;
  }
  int get_answer(int here) {
    while (!pq[here].empty() && is_del[pq[here].top()]) pq[here].pop();
    if (pq[here].empty()) return -1;
    else return pq[here].top();
  }
};

Trie trie;
int here = 0;

int main() {
  #ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  #endif

  cin.tie(NULL); cout.tie(NULL);
  ios_base::sync_with_stdio(false);

  trie.init();

  int n; cin >> n;
  while (n--) {
    string op; cin >> op;

    if (op == "add") {
      int id;
      string s;
      cin >> id >> s;
      trie.add(s, id);
    } else if (op == "append") {
      string s; cin >> s;
      here = trie.append(s, here);
    } else if (op == "backspace") {
      int x; cin >> x;
      here = trie.backspace(x, here);
    } else if (op == "delete") {
      int id; cin >> id;
      trie.is_del[id] = 1;
    }

    cout << trie.get_answer(here) << '\n';
  }
}
