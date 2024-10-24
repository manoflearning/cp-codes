#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 1010101;
const int MAXM = 1010101;

int n, m;
vector<int> a, b;

void input() {
    cin >> n >> m;
    a.resize(n);
    b.resize(m);
    for (auto& i : a) cin >> i;
    for (auto& i : b) cin >> i;
}

namespace value_comp {
vector<int> bb;
void value_comp() {
    bb.push_back(-1);
    for (auto &i : b) bb.push_back(i);
    sort(all(bb));
    bb.erase(unique(all(bb)), bb.end());
    for (auto &i : b)
        i = lower_bound(all(bb), i) - bb.begin();
}
};

namespace solve {
struct Fenwick { // 0-indexed
  int flag, cnt; // array size
  vector<ll> arr, t;
  void build(int n) {
    arr.clear();
    t.clear();
    for (flag = 1; flag < n; flag <<= 1, cnt++);
    arr.resize(flag);
    t.resize(flag);
  }
  void add(int p, ll value) { // add value at position p
    arr[p] += value;
    while (p < flag) {
      t[p] += value;
      p |= p + 1;
    }
  }
  void modify(int p, ll value) { // set value at position p
    add(p, value - arr[p]);
  };
  ll query(int x) {
    ll ret = 0;
    while (x >= 0) ret += t[x], x = (x & (x + 1)) - 1;
    return ret;
  }
  ll query(int l, int r) {
    return query(r) - (l ? query(l - 1) : 0);
  }
} fw;

int cntl[MAXN], cntr[MAXN];
vector<int> get_pi(const vector<int> &P) {
    fw.build(n + 1);
    for (int i = 0; i < sz(P); i++) {
        cntl[i] = fw.query(1, P[i] - 1);
        cntr[i] = fw.query(P[i] + 1, n);
        fw.add(P[i], 1);
    }
    fw.build(n + 1);
    vector<int> pi(sz(P));
    for (int i = 1, j = 0; i < sz(P); i++) {
        while (j > 0 && !(fw.query(1, P[i] - 1) == cntl[j] && fw.query(P[i] + 1, n) == cntr[j])) {
            for (int k = i - j; k < i - pi[j - 1]; k++) fw.add(P[k], -1);
            j = pi[j - 1];
        }
        if (fw.query(1, P[i] - 1) == cntl[j] && fw.query(P[i] + 1, n) == cntr[j]) {
            pi[i] = ++j;
            fw.add(P[i], 1);
        }
    }
    return pi;
}

vector<int> kmp(const vector<int> &T, const vector<int> &P) {
    vector<int> pi = get_pi(P);
    vector<int> ret;
    fw.build(m + 1);
    for (int i = 0, j = 0; i < sz(T); i++) {
        while (j > 0 && !(fw.query(1, T[i] - 1) == cntl[j] && fw.query(T[i] + 1, m) == cntr[j])) {
            for (int k = i - j; k < i - pi[j - 1]; k++) fw.add(T[k], -1);
            j = pi[j - 1];
        }
        if (fw.query(1, T[i] - 1) == cntl[j] && fw.query(T[i] + 1, m) == cntr[j]) {
            if (j == sz(P) - 1) {
                ret.push_back(i - sz(P) + 1);
                for (int k = i - j; k <= i - pi[j]; k++) fw.add(T[k], -1);
                j = pi[j];
            } else ++j;
            fw.add(T[i], 1);
        }
    }
    return ret;
}
};

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    value_comp::value_comp();

    vector<int> ra(n);
    for (int i = 0; i < n; i++) ra[a[i] - 1] = i + 1;

    vector<int> ans = solve::kmp(b, ra);

    cout << sz(ans) << '\n';
    for (auto &i : ans) cout << i + 1 << ' ';
}
