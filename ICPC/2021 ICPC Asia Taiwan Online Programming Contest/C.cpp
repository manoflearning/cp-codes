#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Fenwick { // 1-indexed
  int flag;
  vector<ll> t;
  void build(int N) {
    flag = N;
    t.resize(flag + 1);
  }
  void modify(int l, int r, int val) { // add a val to all elements in interval [l, r]
    for (; l <= flag; l += l & -l) t[l] += val;
    for (r++; r <= flag; r += r & -r) t[r] -= val;
  }
  ll query(int x) {
    ll ret = 0;
    for (; x; x ^= x & -x) ret += t[x];
    return ret;
  }
} fw;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    int n; cin >> n;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) cin >> p[i];

    fw.build(n);

    ll ans = 0;
    for (int i = n; i >= 1; i--) {
        ans += (i - (p[i] + fw.query(p[i])));
        fw.modify(p[i] + 1, n, -1);
    }

    cout << ans;
}
