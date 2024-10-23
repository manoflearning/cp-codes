#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 101010;
const ll INF = 1e18;

int n;
ll a[MAXN], psum[MAXN];

struct Node {
    ll mn, mx, opt;
    Node operator+(const Node& o) const {
        Node ret;
        ret.mn = min({mn, o.mn});
        ret.mx = max({mx, o.mx});
        ret.opt = max({opt, o.opt, o.mx - mn});
        return ret;
    }
};
int flag;
struct Seg {
    vector<Node> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1, {INF, -INF, -INF});
        for (int i = flag; i < flag + n; i++)
            t[i] = {psum[i - flag + 1], psum[i - flag + 1], -INF};
        for (int i = flag - 1; i >= 1; i--)
            t[i] = t[i << 1] + t[i << 1 | 1];
    }
    Node query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return {INF, -INF, -INF};
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
}seg;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        psum[i + 1] = a[i] + psum[i];
    }

    seg.build(n + 1);

    int q; cin >> q;
    while (q--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x2++, y2++;

        if (y1 < x2) {
            ll mn = seg.query(x1, y1).mn;
            ll mx = seg.query(x2, y2).mx;
            cout << mx - mn << '\n';
        } else {
            ll ans = seg.query(x2, y1).opt;
            ans = max(ans, seg.query(y1 + 1, y2).mx - seg.query(x1, y1).mn);
            ans = max(ans, seg.query(x2, y2).mx - seg.query(x1, x2 - 1).mn);
            cout << ans << '\n';
        }
    }
}
