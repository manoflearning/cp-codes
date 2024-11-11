#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 101010;
const int MAXQ = 101010;
const int MAXM = 1010101;

int flag; // array size
struct Seg {
  vector<ll> t;
  void build(int n) {
    for (flag = 1; flag < n; flag <<= 1);
    t.resize(flag << 1);
    for (int i = flag; i < flag + n; i++) t[i] = 1;
    for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
  }
  void modify(int p, ll value) { // set value at position p
    for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
  }
  ll kth(ll k, int n = 1) { // find the kth smallest number (1-indexed)
    assert(t[n] >= k);
    if (flag <= n) return n - flag + 1;
    if (k <= t[n << 1]) return kth(k, n << 1);
    else return kth(k - t[n << 1], n << 1 | 1);
  }
} seg;

int n, m, q;
int a[MAXN];

struct Query {
    ll kth, kth_fr_fixed;
    int idx;
};
Query qu[MAXQ];

ll cnt[MAXM], pcnt[MAXM];
int idx_lm[MAXM];

int ans1[MAXQ], ans2[MAXQ];
vector<Query> fr_to_sc[MAXM];

void input() {
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= q; i++) {
        cin >> qu[i].kth;
        qu[i].idx = i;
    }
}

void cal_fr_var() {
    set<int> st;
    for (int i = 1; i <= m; i++) cnt[i] = m;
    for (int i = n; i >= 1; i--) {
        cnt[a[i]] = m - sz(st);
        st.insert(a[i]);
        idx_lm[a[i]] = i;
    }

    sort(qu + 1, qu + q + 1, [](const Query &lhs, const Query &rhs) {
        return lhs.kth < rhs.kth;
    });

    for (int i = 1; i <= m; i++) {
        pcnt[i] = cnt[i] + pcnt[i - 1];
    }

    int ptr = 1;
    for (int i = 1; i <= q; i++) {
        auto &it = qu[i];
        while (ptr <= m && pcnt[ptr] < it.kth) ptr++;
        if (ptr == m + 1) ans1[it.idx] = ans2[it.idx] = -1;
        else {
            ans1[it.idx] = ptr;
            it.kth_fr_fixed = it.kth - pcnt[ptr - 1];

            fr_to_sc[ans1[it.idx]].push_back(it);
        }
    }
}

void cal_sc_var() {
    seg.build(m);

    set<int> st;
    for (int i = n; i >= 1; i--) {
        if (i == idx_lm[a[i]]) {
            for (auto &it : fr_to_sc[a[i]]) {
                ans2[it.idx] = seg.kth(it.kth_fr_fixed);
            }
        }

        seg.modify(a[i], 0);
    }

    for (int i = 1; i <= m; i++) {
        if (idx_lm[i] == 0) {
            for (auto &it : fr_to_sc[i]) {
                ans2[it.idx] = it.kth_fr_fixed;
            }
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    cal_fr_var();

    cal_sc_var();

    for (int i = 1; i <= q; i++)
        cout << ans1[i] << ' ' << ans2[i] << '\n';
}
