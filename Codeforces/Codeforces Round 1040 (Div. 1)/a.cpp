#include <bits/stdc++.h>
using namespace std;
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

struct UF {
  vector<int> uf;
  void build(int N) {
    uf.clear();
    uf.resize(N + 1, -1);
  }
  int find(int v) {
    if (uf[v] < 0) return v;
    return uf[v] = find(uf[v]);
  }
  void merge(int u, int v) {
    int U = find(u), V = find(v);
    if (U == V) return;
    uf[U] += uf[V];
    uf[V] = U;
  }
} uf;

int n;
vector<int> a, b;

void init() {}

void input() {
    cin >> n;
    a.resize(n);
    b.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
}

int main() {
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    int tc; cin >> tc;
    while (tc--) {
        init();
        
        input();
        
        vector<int> ord(n);
        iota(all(ord), 0);
        sort(all(ord), [&](int i, int j) {
            return (a[i] ^ a[j] ? a[i] < a[j] : b[i] < b[j]); 
        });
        
        vector<int> ans;
        uf.build(2 * n);
        for (auto i : ord) {
            if (uf.find(a[i]) == uf.find(b[i])) {
                continue;
            }
            uf.merge(a[i], b[i]);
            ans.push_back(i);
        }
        
        sort(all(ans));
        cout << sz(ans) << '\n';
        for (auto &i : ans) cout << i + 1 << ' ';
        cout << '\n';
    }
}
