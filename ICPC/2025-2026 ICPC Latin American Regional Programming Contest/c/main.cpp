#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr ll INF = 1e18;
constexpr int N = 101010;
constexpr int H = 101010;

int flag;
struct Seg {
    struct node {
        ll cnt, sum;
        node operator+(const node &rhs) const {
            node ret{};
            ret.cnt = cnt + rhs.cnt;
            ret.sum = sum + rhs.sum;
            return ret;
        }
    };
    vector<node> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1, {0, 0});
    }
    void add(int p, ll val) {
        t[p + flag - 1].cnt += val;
        t[p + flag - 1].sum += val * p;
        for (p += flag - 1; p > 1; p >>= 1)
            t[p >> 1] = t[p] + t[p ^ 1];
    }
    node query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return {0, 0};
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
    int kth(int k, int n = 1, int nl = 1, int nr = flag) {
        if (nl == nr) return nl;

        int mid = (nl + nr) >> 1;
        if (k <= t[n << 1].cnt) return kth(k, n << 1, nl, mid);
        else return kth(k - t[n << 1].cnt, n << 1 | 1, mid + 1, nr);
    }
} seg;

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}

struct frac {
    ll n, d;
    frac(ll _n, ll _d) {
        ll g = gcd(_n, _d);
        _n /= g, _d /= g;
        n = _n, d = _d;
    }
    bool operator<(const frac &rhs) const {
        return n * rhs.d < rhs.n * d;
    }
    bool operator==(const frac &rhs) const {
        return n * rhs.d == rhs.n * d;
    }
};

int n, s, k;
ll h[N], l[N], u[N];

set<tuple<frac, int, bool>> st;

frac ans{(ll)1e12, 1};

void input() {
    cin >> n >> s >> k;
    for (int i = 1; i <= n; i++) {
        cin >> h[i] >> l[i] >> u[i];

        st.insert({frac{l[i], h[i]}, i, 0});
        st.insert({frac{u[i], h[i]}, i, 1});
    }
}

void solve() {
    seg.build(H);

    for (auto &[pay, idx, is_exit] : st) {
        if (!is_exit) {
            seg.add(h[idx], k / h[idx]);
        } else {
            seg.add(h[idx], -(k / h[idx]));
        }

        int mxh = seg.kth(s);

        auto res1 = seg.query(1, mxh - 1);
        auto res2 = seg.query(mxh, mxh);

        if (res1.cnt + res2.cnt < s) continue;

        ll total_h = res1.sum + (s - res1.cnt) * mxh;

        frac res{total_h * pay.n, pay.d};
        if (res < ans) ans = res;
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    input();

    solve();

    if (ans == frac{(ll)1e12, 1}) {
        cout << "*";
    } else {
        cout << ans.n << ' ' << ans.d;
    }
}
    