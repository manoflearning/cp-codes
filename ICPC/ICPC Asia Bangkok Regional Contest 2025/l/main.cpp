#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

constexpr ll INF = 4e18;
constexpr int N = 101010;
constexpr int Q = 101010;

struct node {
    ll mn, mx;
    // bool operator!=(const node &rhs) const {
    //     return pll{mn, mx} != pll{rhs.mn, rhs.mx};
    // }
};
node minmax(const node &lhs, const node &rhs) {
    return {min(lhs.mn, rhs.mn), min(lhs.mx, rhs.mx)};
}

const node e = node{INF, INF};

int flag;
struct Seg {
    vector<node> t;
    void build(int n) {
        t.clear();
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1, e);
    }
    void modify(int p, node val) {
        p += flag - 1;
        t[p] = minmax(t[p], val);
        for (; p > 1; p >>= 1)
            t[p >> 1] = minmax(t[p], t[p ^ 1]);
    }
    node query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return e;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return minmax(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
} seg;

int n, q;
ll a, b;
struct point { ll x, y, c; };
point po[N];
struct query { ll s, t; int idx; };
query qu[Q];
vector<ll> ans(Q, INF);

void input() {
    cin >> n >> q >> a >> b;
    for (int i = 1; i <= n; i++) {
        cin >> po[i].x >> po[i].y >> po[i].c;
    }
    for (int i = 1; i <= q; i++) {
        cin >> qu[i].s >> qu[i].t;
        qu[i].idx = i;
    }
}

vector<ll> cc;
void coor_comp() {
    cc.push_back(-INF);

    for (int i = 1; i <= n; i++)
        cc.push_back(po[i].x);
    for (int i = 1; i <= q; i++)
        cc.push_back(qu[i].s);

    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());

    for (int i = 1; i <= n; i++) {
        po[i].x = lower_bound(all(cc), po[i].x) - cc.begin();
    }
    for (int i = 1; i <= q; i++) {
        qu[i].s = lower_bound(all(cc), qu[i].s) - cc.begin();
    }
}

void solve() {
    sort(po + 1, po + n + 1, [&](const point &lhs, const point &rhs) {
        return lhs.y < rhs.y;
    });

    sort(qu + 1, qu + q + 1, [&](const query &lhs, const query &rhs) {
        return lhs.t < rhs.t;
    });

    seg.build(sz(cc) - 1);

    int po_idx = 1;
    for (int i = 1; i <= q; i++) {
        while (po_idx <= n && po[po_idx].y <= qu[i].t) {
            seg.modify(po[po_idx].x, node{
                po[po_idx].c + a * cc[po[po_idx].x] - b * po[po_idx].y,
                po[po_idx].c - a * cc[po[po_idx].x] - b * po[po_idx].y,
            });
            po_idx++;
        }

        ans[qu[i].idx] = min({
            ans[qu[i].idx],
            seg.query(qu[i].s, sz(cc) - 1).mn - a * cc[qu[i].s] + b * qu[i].t,
            seg.query(1, qu[i].s).mx + a * cc[qu[i].s] + b * qu[i].t,
        });
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    cin.tie(nullptr)->sync_with_stdio(false);

    input();

    coor_comp();

    solve();
    
    for (int i = 1; i <= n; i++)
        po[i].y = (int)1e9 - po[i].y;
    for (int i = 1; i <= q; i++)
        qu[i].t = (int)1e9 - qu[i].t;
    
    solve();

    for (int i = 1; i <= q; i++) {
        cout << ans[i] << '\n';
    }
}