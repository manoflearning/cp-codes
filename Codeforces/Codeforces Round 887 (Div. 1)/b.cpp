#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int flag;    // array size
struct Seg { // 1-indexed
  vector<ll> t;
    void build(int n) {
        t.clear();
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(2 * flag);
        // for (int i = flag; i < flag + n; i++) cin >> t[i];
        // for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
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
        int n; cin >> n;

        vector<int> a(n);
        for (auto &i : a) cin >> i;

        vector<int> ord(n);
        iota(all(ord), 0);
        sort(all(ord), [&](int p1, int p2) {
            return a[p1] > a[p2];
        });

        seg.build(3 * n);
        vector<bool> vis(3 * n);
        vis[0] = 1;

        bool is_valid = 1;
        vector<int> ans(n);

        int now = n;
        for (int i = 0; i < n; i++) {
            int j = ord[i];

            while (now >= -n) {
                int res = 0;

                res += seg.query(-now + n + 2, 2 * n + 1);
                if (now > 0) {
                    res++;
                    res += abs(now) - 1;
                }

                if (a[j] == res && !vis[abs(now)]) break;
                else now--;
            }

            if (now == -n - 1) {
                is_valid = 0;
                break;
            }

            seg.add(now + n + 1, 1);
            vis[abs(now)] = 1;
            ans[j] = now;
            now--;
        }

        if (is_valid) {
            for (int i = 0; i < n; i++) {
                is_valid &= (seg.query(-ans[i] + n + 2, 2 * n + 1) == a[i]);
                // DEBUG
                // cout << a[i] << ' ' << ans[i] << ' ' << seg.query(-ans[i] + n + 2, 2 * n + 1) << '\n';
            }
        }

        if (is_valid) {
            cout << "YES\n";
            for (auto &i : ans) cout << i << ' ';
            cout << '\n';
        } else {
            cout << "NO\n";
        }
    }
}
