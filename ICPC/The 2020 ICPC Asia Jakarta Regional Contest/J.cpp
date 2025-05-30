#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 7;
const int FLAG = 131072;

struct SegMax {
    vector<int> t;
    void build() { t.resize(2 * FLAG, -INF); }
    void modify(int p, int val) {
        for (t[p += FLAG - 1] = val; p > 1; p >>= 1)
            t[p >> 1] = max(t[p], t[p ^ 1]);
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = FLAG) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
}segmax, segequal;

struct SegMin {
    vector<int> t;
    void build() { t.resize(2 * FLAG, INF); }
    void modify(int p, int val) {
        for (t[p += FLAG - 1] = val; p > 1; p >>= 1)
            t[p >> 1] = min(t[p], t[p ^ 1]);
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = FLAG) {
        if (nr < l || r < nl) return INF;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
}segmin;

struct SegGcd {
    vector<int> t;
    void build() { t.resize(2 * FLAG, 0); }
    int gcd(int x, int y) {
        if (!y) return x;
        else return gcd(y, x % y);
    }
    void modify(int p, int val) {
        if (val < 0) val *= -1;
        for (t[p += FLAG - 1] = val; p > 1; p >>= 1)
            t[p >> 1] = gcd(t[p], t[p ^ 1]);
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = FLAG) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return gcd(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
}seggcd;

int n, q;
int a[101010];
map<int, set<int>> mp;
int closestEqual[101010];

void input() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

void buildSegmentTree() {
    segmax.build();
    segequal.build();
    segmin.build();
    seggcd.build();
    for (int i = 1; i <= n; i++) {
        segmax.modify(i, a[i]);
        if (mp.count(a[i])) closestEqual[i] = *mp[a[i]].rbegin();
        else closestEqual[i] = -1;
        mp[a[i]].insert(i);
        segequal.modify(i, closestEqual[i]);
        segmin.modify(i, a[i]);
        if (i < n) seggcd.modify(i, a[i + 1] - a[i]);
    }
}

void modifyEqual(set<int>& s, int mid) {
    auto it = s.lower_bound(mid);
    if (it == s.end()) return;
    int idx = *it;
    if (it == s.begin()) closestEqual[idx] = -1;
    else {
        it--;
        closestEqual[idx] = *it;
    }
    segequal.modify(idx, closestEqual[idx]);
}

void solve() {
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            int x, y;
            cin >> x >> y;

            int tmp = a[x];
            a[x] = y;
            segmax.modify(x, a[x]);

            set<int>& olds = mp[tmp];
            set<int>& news = mp[a[x]];
            olds.erase(x);
            news.insert(x);
            modifyEqual(olds, x + 1);
            modifyEqual(news, x);
            modifyEqual(news, x + 1);

            segmin.modify(x, a[x]);
            if (1 < x) seggcd.modify(x - 1, a[x] - a[x - 1]);
            if (x < n) seggcd.modify(x, a[x + 1] - a[x]);
        }
        if (op == 2) {
            int L, R;
            cin >> L >> R;

            int delta = segmax.query(L, R) - segmin.query(L, R);
            int g = seggcd.query(L, R - 1);

            if (delta == 0) cout << "YES\n";
            else if (segequal.query(L, R) >= L) cout << "NO\n";
            else if (delta % (R - L)) cout << "NO\n";
            else if (delta / (R - L) != g) cout << "NO\n";
            else cout << "YES\n";
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

    buildSegmentTree();

    solve();
}