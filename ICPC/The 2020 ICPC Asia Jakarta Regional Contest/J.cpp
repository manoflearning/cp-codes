#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()

const int INF = 1e9 + 7;

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}

struct Node {
    ll mn, mx, sum, g;
    Node operator+(const Node& rhs) const {
        Node ret;
        ret.mn = min(mn, rhs.mn);
        ret.mx = max(mx, rhs.mx);
        ret.sum = sum + rhs.sum;
        ret.g = gcd(g, rhs.g);
        return ret;
    }
};
const Node e = { INF, 0, 0, 0 };

int flag;
struct Seg {
    vector<Node> t;
    void build(int n) {
        t.clear();
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1, e);
    }
    void modify(int p, int val) {
        t[p + flag - 1].mn = val;
        t[p + flag - 1].mx = val;
        if (p > 1) t[p + flag - 1].g = abs(val - t[p + flag - 2].mx);
        else t[p + flag - 1].g = 0;
        t[p + flag - 1].sum = val;

        for (p += flag - 1; p > 1; p >>= 1)
            t[p >> 1] = t[p] + t[p ^ 1];
    }
    Node query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return e;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
}seg;

int n, q;
vector<int> a(101010);

void input() {
    cin >> n >> q;
    seg.build(n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        seg.modify(i, a[i]);
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

    while (q--) {
        int op, x, y;
        cin >> op >> x >> y;

        if (op == 1) {
            seg.modify(x, y);
            if (x < n) seg.modify(x + 1, seg.query(x + 1, x + 1).mn);
        }
        if (op == 2) {
            Node res = seg.query(x, y);
            res.g = seg.query(x + 1, y).g;

            if ((res.mx - res.mn) % (y - x)) {
                // cout << 1 << '\n';
                cout << "NO" << '\n';
                continue;
            }
            
            ll gap = (res.mx - res.mn) / (y - x);

            if (res.sum != (res.mn) * (y - x + 1) + gap * (y - x + 1) * (y - x) / 2) {
                // cout << 2 << '\n';
                cout << "NO" << '\n';
                continue;
            }
            
            if (res.g != gap) {
                // cout << res.g << ' ' << gap << '\n';
                // cout << 3 << '\n';
                cout << "NO" << '\n';
                continue;
            }

            cout << "YES" << '\n';
        }
    }
}