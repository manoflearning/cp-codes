#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define sz(x) (int)(x).size()

int n;
struct Point { ll x, y; };
vector<Point> p;

int flag;
struct Seg {
    vector<ll> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void modify(int p, ll val) {
        t[p + flag - 1] = max(t[p + flag - 1], val);
        for (p += flag - 1; p > 1; p >>= 1) {
            t[p >> 1] = max(t[p], t[p ^ 1]);
        }
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
} seg;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    p.resize(n);
    for (auto &i : p) {
        cin >> i.x >> i.y;
    }

    for (auto &i : p) {
        ll x_prv = i.x, y_prv = i.y;
        i.x = x_prv - y_prv;
        i.y = x_prv + y_prv + 2'000'000 + 1;
    }

    sort(p.begin(), p.end(),
        [&](const Point &i, const Point &j) {
            if (i.x ^ j.x) return i.x < j.x;
            return i.y > j.y;
        });

    ll ans = 0;
    seg.build(4'040'404);
    for (auto &i : p) {
        ll res = seg.query(1, i.y - 1) + 1;
        ans = max(ans, res);
        seg.modify(i.y, res);
    }

    cout << ans;
}
