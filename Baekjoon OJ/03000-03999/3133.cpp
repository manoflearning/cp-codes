#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;

struct Node {
    ll w, cnt;
    Node operator+(const Node& rhs) {
        Node ret = { 0, 0 };
        ret.w = max(w, rhs.w);
        ret.cnt += (ret.w == w ? cnt : 0);
        ret.cnt += (ret.w == rhs.w ? rhs.cnt : 0);
        ret.cnt %= MOD;
        return ret;
    }
};

int flag;
struct Seg {
    vector<Node> t;
    void build() {
        for (flag = 1; flag < 600000; flag <<= 1);
        t.resize(flag << 1);
    }
    void modify(int p, ll w, ll cnt) {
        p += flag - 1;
        if (t[p].w < w) {
            t[p].w = w, t[p].cnt = cnt;
        }
        else if (t[p].w == w) {
            t[p].cnt += cnt, t[p].cnt %= MOD;
        }
        else if (t[p].w > w) return;

        for (; p > 1; p >>= 1) 
            t[p >> 1] = t[p] + t[p ^ 1];
    }
    Node query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return { 0, 0 };
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
}seg;

struct Point { ll x, y; };

int n;
vector<Point> p;
ll dp1[303030], dp2[303030];

void input() {
    cin >> n;
    p.resize(n);
    for (auto& i : p)
        cin >> i.x >> i.y;
}

void cc() {
    vector<ll> c(1, -INF);
    for (auto& i : p) {
        c.push_back(i.x);
        c.push_back(i.y);
    }

    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());

    for (auto& i : p) {
        i.x = lower_bound(c.begin(), c.end(), i.x) - c.begin();
        i.y = lower_bound(c.begin(), c.end(), i.y) - c.begin();
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    cc();

    sort(p.begin(), p.end(), [&](const Point& lhs, const Point& rhs) {
        if (lhs.x ^ rhs.x) return lhs.x < rhs.x;
        else return lhs.y > rhs.y;
    });

    seg.build();
    for (int i = 0; i < n; i++) {
        auto it = p[i];

        Node res = seg.query(1, it.y - 1);
        if (res.w == 0) dp1[i] = dp2[i] = 1;
        else dp1[i] = res.w + 1, dp2[i] = res.cnt;

        seg.modify(p[i].y, dp1[i], dp2[i]);
    }

    ll ans1 = 0, ans2 = 0;
    for (int i = 0; i < n; i++) {
        if (ans1 < dp1[i]) ans1 = dp1[i], ans2 = dp2[i];
        else if (ans1 == dp1[i]) ans2 = (ans2 + dp2[i]) % MOD;
    }

    cout << ans1 << '\n' << ans2;
}