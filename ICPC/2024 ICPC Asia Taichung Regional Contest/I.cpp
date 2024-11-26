#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int st = 33;
const int MAXC = 126 - 33 + 1;

struct trie {
  trie *child[MAXC];
  bool term;
  trie() {
    fill(child, child + MAXC, nullptr);
    term = false;
  }
  ~trie() {
    for (int i = 0; i < MAXC; i++)
      if (child[i]) delete child[i];
  }
  void insert(const string &s, int key = 0) {
    if (s.size() == key) term = true;
    else {
      int next = s[key] - st;
      if (!child[next]) child[next] = new trie;
      child[next]->insert(s, key + 1);
    }
  }
  bool find(const string &s, int key = 0) {
    if (s.size() == key) return term;
    else {
      int next = s[key] - st;
      if (!child[next]) return false;
      else return child[next]->find(s, key + 1);
    }
  }
};

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    trie *root = new trie;

    int n; cin >> n;
    while (n--) {
        string op; cin >> op;

        if (op == "add") {
            int id;
            string s;
            cin >> id >> s;
            
        } else if (op == "append") {

        } else if (op == "backspace") {

        } else if (op == "delete") {

        }
    }

    delete root;
}
