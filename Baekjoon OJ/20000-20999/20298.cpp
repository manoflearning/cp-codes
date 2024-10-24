#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 101010;
const int MAXK = 101010;

int n, k;
vector<int> a, b;

void input() {
    cin >> n >> k;
    a.resize(n << 1);
    b.resize(k);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i + n] = a[i];
    }
    for (int i = 0; i < k; i++) cin >> b[i];
}

vector<int> aa, bb;

void coor_comp() {
    aa.push_back(-1);
    bb.push_back(-1);
    for (int i = 0; i < n; i++) aa.push_back(a[i]);
    for (int i = 0; i < k; i++) bb.push_back(b[i]);

    sort(all(aa));
    sort(all(bb));
    aa.erase(unique(all(aa)), aa.end());
    bb.erase(unique(all(bb)), bb.end());

    for (int i = 0; i < 2 * n; i++)
        a[i] = lower_bound(all(aa), a[i]) - aa.begin();
    for (int i = 0; i < k; i++)
        b[i] = lower_bound(all(bb), b[i]) - bb.begin();
}

int flag; // array size
struct Seg {
  vector<ll> t;
  void build(int n) {
    t.clear();
    for (flag = 1; flag < n; flag <<= 1);
    t.resize(flag << 1);
  }
  void add(int p, ll value) { // add value at position p
    for (t[p += flag - 1] += value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
  }
  ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) { // sum on interval [l, r]
    if (r < nl || nr < l) return 0;
    if (l <= nl && nr <= r) return t[n];
    int mid = (nl + nr) / 2;
    return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
  }
} seg;

vector<int> front(MAXN), back(MAXN);
vector<int> getpi(const vector<int> &P) {
  seg.build(n);
  for (int i = 0; i < sz(P); i++) {
    front[i] = seg.query(1, P[i] - 1);
    back[i] = seg.query(P[i] + 1, n);
    seg.add(P[i], 1);
  }
  
  vector<int> pi(sz(P));
  seg.build(n);
  for (int i = 1, j = 0; i < sz(P); i++) {
    while (j > 0 && !(seg.query(1, P[i] - 1) == front[j] && seg.query(P[i] + 1, n) == back[j])) {
        for (int k = i - j; k < i - pi[j - 1]; k++) seg.add(P[k], -1);
        j = pi[j - 1];
    }
    if (seg.query(1, P[i] - 1) == front[j] && seg.query(P[i] + 1, n) == back[j]) {
        pi[i] = ++j;
        seg.add(P[i], 1);
    }
  }
  return pi;
}
int kmp(const vector<int> &T, const vector<int> &P) {
  int ret = 0;
  vector<int> pi = getpi(P);

  seg.build(n);

  for (int i = 0, j = 0; i < sz(T); i++) {
    while (j > 0 && !(seg.query(1, T[i] - 1) == front[j] && seg.query(T[i] + 1, n) == back[j])) {
        for (int k = i - j; k < i - pi[j - 1]; k++) seg.add(T[k], -1);
        j = pi[j - 1];
    }

    if (seg.query(1, T[i] - 1) == front[j] && seg.query(T[i] + 1, n) == back[j]) {
      if (j == sz(P) - 1) {
        if (i - k + 1 < n) {
            ret++;
            // cout << i - k + 1 << '\n';
        }
        for (int k = i - j; k <= i - pi[j]; k++) seg.add(T[k], -1);
        j = pi[j];
      } else ++j;
      seg.add(T[i], 1);
    }
  }
  return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    coor_comp();

    cout << kmp(a, b);
}
