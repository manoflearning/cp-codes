#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXN = 101010;
const int MAXQ = 101010;
const int INF = 1e9 + 7;

struct Node {
    ll mx_all, mx_l, mx_r, mx;
    Node operator+(const Node& rhs) const {
        Node ret;
        ret.mx_all = mx_all + rhs.mx_all;
        ret.mx_l = max(mx_l, mx_all + rhs.mx_l);
        ret.mx_r = max(mx_r + rhs.mx_all, rhs.mx_r);
        ret.mx = max({ mx, rhs.mx, mx_r + rhs.mx_l });
        return ret;
    }
};

const Node e = { -INF, -INF, -INF, -INF };

int flag;
struct Seg {
    vector<Node> t;
    void build(int n) {
        t.clear();
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1, e);
        for (int i = flag - 1; i >= 1; i--) {
            t[i] = t[i << 1] + t[i << 1 | 1];
        }
    }
    void add(int p) {
        for (t[p += flag - 1] = { 1, 1, 1, 1 }; p > 1; p >>= 1) {
            if (p & 1) t[p >> 1] = t[p ^ 1] + t[p];
            else t[p >> 1] = t[p] + t[p ^ 1];
        }
    }
    Node query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (r < nl || nr < l) return e;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
}seg;

int n;
vector<int> h(MAXN);

int q;
struct Query { int s, e, w; };
vector<Query> qu(MAXQ);

void input() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> h[i];
    cin >> q;
    for (int i = 1; i <= q; i++) {
        cin >> qu[i].s >> qu[i].e >> qu[i].w;
    }
}

vector<int> l(MAXQ, 1), r(MAXQ, 1e9), mid(MAXQ);
void pbs() {
    vector<int> ordh(n);
    iota(all(ordh), 1);

    sort(all(ordh), [&](int p1, int p2) {
        return h[p1] > h[p2];
    });

    for (int k = 0; k < 40; k++) {
        for (int i = 1; i <= q; i++) {
            if (l[i] == r[i]) mid[i] = -1;
            else mid[i] = (l[i] + r[i] + 1) >> 1;
        }

        vector<int> ordq(q);
        iota(all(ordq), 1);

        sort(all(ordq), [&](int p1, int p2) {
            return mid[p1] > mid[p2];
        });

        int ordh_idx = 0;
        seg.build(n);
        for (auto& i : ordq) {
            if (mid[i] == -1) break;

            while (ordh_idx < sz(ordh) && h[ordh[ordh_idx]] >= mid[i]) {
                seg.add(ordh[ordh_idx++]);
            }

            if (seg.query(qu[i].s, qu[i].e).mx >= qu[i].w) l[i] = mid[i];
            else r[i] = mid[i] - 1;
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

    pbs();

    for (int i = 1; i <= q; i++)
        cout << l[i] << '\n';
}
