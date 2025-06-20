#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int flag;    // array size
struct Seg { // 1-indexed
    vector<ll> t;
    void build(int n) {
        t.clear();
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(2 * flag);
    }
    void add(int p, ll value) { // set value at position p
        for (t[p += flag - 1] += value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) { // sum on interval [l, r]
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) / 2;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
} seg;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;

        vector<int> a(n * m);
        for (auto &i : a) cin >> i;

        {
            vector<int> cc;
            for (auto &i : a) {
                cc.push_back(i);
            }

            sort(all(cc));
            cc.erase(unique(all(cc)), cc.end());

            for (auto &i : a) {
                i = lower_bound(all(cc), i) - cc.begin() + 1;
            }
        }

        seg.build(n * m);

        ll ans = 0;
        for (int i = 0; i < n * m; i++) {
            ans += seg.query(1, a[i] - 1);
            seg.add(a[i], 1);
        }

        cout << ans << '\n';
    }
}
