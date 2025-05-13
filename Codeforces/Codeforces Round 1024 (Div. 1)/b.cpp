#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int flag;    // array size
struct Seg { // 1-indexed
  vector<ll> t;
  void init() { t.clear(); }
  void build(int n) {
    for (flag = 1; flag < n; flag <<= 1);
    t.resize(2 * flag);
  }
  void add(int p, ll value) {
    for (t[p += flag - 1] += value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
  }
  ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) { // sum on interval [l, r]
    if (r < nl || nr < l) return 0;
    if (l <= nl && nr <= r) return t[n];
    int mid = (nl + nr) / 2;
    return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
  }
} sego, sege;

int n;
vector<int> a;

void init() {
    sego.init();
    sege.init();
}

void input() {
    cin >> n;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();
        
        input();

        sego.build(n);
        sege.build(n);

        ll inv_cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (i & 1) {
                inv_cnt += sego.query(a[i] + 1, n);
                sego.add(a[i], 1);
            } else {
                inv_cnt += sege.query(a[i] + 1, n);
                sege.add(a[i], 1);
            }
        }

        vector<int> odd, eve;
        for (int i = 1; i <= n; i++) {
            if (i & 1) {
                odd.push_back(a[i]);
            } else {
                eve.push_back(a[i]);
            }
        }

        sort(all(odd));
        sort(all(eve));
        
        vector<int> ans;
        int idx = 0;
        while (idx < sz(odd) || idx < sz(eve)) {
            if (idx < sz(odd)) ans.push_back(odd[idx]);
            if (idx < sz(eve)) ans.push_back(eve[idx]);
            idx++;
        }

        if (inv_cnt & 1) {
            swap(ans[n - 3], ans[n - 1]);
        }

        for (auto &i : ans) cout << i << ' ';
        cout << '\n';

        // vector<int> even;
        // for (int i = 1; i <= n; i += 2) {
        //     even.push_back(i);
        // }

        // sort(all(even), [&](int lhs, int rhs) {
        //     return a[lhs] < a[rhs];
        // });

        // seg.build(n);

        // int cnt = 0;
        // vector<int> odd;
        // for (int i = 0; i < sz(even); i++) {
        //     int idx = even[i] + 1;
        //     if (idx <= n) {
        //         cnt += seg.query(a[idx] + 1, n);
        //         seg.add(a[idx], 1);

        //         odd.push_back(idx);
        //     }
        // }

        // sort(all(odd), [&](int lhs, int rhs) {
        //     return a[lhs] < a[rhs];
        // });

        // vector<int> ans;

        // int idx = 0;
        // while (idx < sz(even) || idx < sz(odd)) {
        //     if (idx < sz(even)) ans.push_back(a[even[idx]]);
        //     if (idx < sz(odd)) ans.push_back(a[odd[idx]]);
        //     idx++;
        // }

        // if (cnt & 1) {
        //     swap(ans[n - 3], ans[n - 1]);
        // }

        // for (auto &i : ans) cout << i << ' ';
        // cout << '\n';
    }
}
