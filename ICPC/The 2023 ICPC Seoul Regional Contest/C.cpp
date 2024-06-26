#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;

int flag;
struct SegEdge {
    vector<pair<int, pii>> t;
    void build(int n, const vector<int>& v) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1, { INF, { INF, INF } });
        for (int i = 1; i + 2 < sz(v); i += 2) {
            int nl = v[i - 1], nr = v[i + 1], h = v[i];
            t[nl + flag - 1] = { h, { nl, nr }};
        }
        for (int i = flag - 1; i >= 1; i--) {
            t[i] = min(t[i << 1], t[i << 1 | 1]);
        }
    }
    pair<int, pii> query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return { INF, { INF, INF } };
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
}segedge;

struct SegDot {
    vector<pii> t;
    void build(int n, const vector<pii>& a) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1, { INF, INF });
        for (auto& i : a) {
            int p = i.fr + flag - 1;
            if (t[p].fr == INF) t[p] = { i.sc, i.fr };
            else t[p] = max(t[p], { i.sc, i.fr });
        }
        for (int i = flag - 1; i >= 1; i--) {
            t[i] = min(t[i << 1], t[i << 1 | 1]);
        }
    }
    void del(int p) {
        for (t[p += flag - 1] = { INF, INF }; p > 1; p >>= 1) {
            t[p >> 1] = min(t[p], t[p ^ 1]);
        }
    }
    pii query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return { INF, INF };
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
}segdot;

int m, n;
vector<int> v;
vector<pii> a;
vector<pii> edges[1010101];

void input() {
    cin >> m >> n;
    v.resize(m);
    for (auto& i : v) {
        cin >> i; i++;
    }
    a.resize(n);
    for (auto& i : a) {
        cin >> i.fr >> i.sc;
        i.fr++, i.sc++;
    }
}

void buildSegmentTree() {
    segedge.build(1010101, v);
    segdot.build(1010101, a);
}

int ans = 0;

void dnc(int l, int r, int lb) {
    // base case
    if (l >= r) return;

    // delete all the dots s.t. y <= lb
    while (1) {
        pii res = segdot.query(l, r);
        if (res.fr <= lb) segdot.del(res.sc);
        else break;
    }

    // find horizonhal edge [nl, nr] s.t. min_y(l ... r) = [nl, nr]_y
    pair<int, pii> edge = segedge.query(l, r - 1);
    int nl = edge.sc.fr, nr = edge.sc.sc, h = edge.fr;

    // if (!(l <= nl && nr <= r && nl <= nr)) {
    //     cout << l << ' ' << r << '\n';
    //     cout << nl << ' ' << nr << '\n';
    //     exit(0);
    // }
    // assert(l <= nl && nr <= r && nl <= nr);

    // if there's a dot in the range of [nl + 1, nr - 1], add 1 to ans
    if (segdot.query(nl + 1, nr - 1).fr != INF) ans++;
    else if (l == nl && nr == r && segdot.query(nl, nr).fr) {
        ans++;
        return;
    }

    // get answer for dnc(l, nl) and dnc(nr, r)
    if (nl != INF) dnc(l, nl, h);
    if (nr != INF) dnc(nr, r, h);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    buildSegmentTree();
    
    dnc(1, 1'000'001, 0);

    cout << ans;
}