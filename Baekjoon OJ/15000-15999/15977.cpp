#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int MAXM = 5;
const int MAXN = 202020;

int flag;
class Seg1D {
public:
    vector<int> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void modify(int p, int val) {
        for (t[p += flag - 1] = val; p > 1; p >>= 1)
            t[p >> 1] = max(t[p], t[p ^ 1]);
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
}seg1d;

int flagy, flagx;
class Seg2D {
public:
    vector<vector<int>> t;
    void build(int sizy, int sizx) {
        for (flagy = 1; flagy < sizy; flagy <<= 1);
        for (flagx = 1; flagx < sizx; flagx <<= 1);
        t.resize(flagy << 1, vector<int>(flagx << 1));
    }
    void modify(int y, int x, int val) {
        int i = y + flagy - 1, j = x + flagx - 1;
        t[i][j] = val;
        
        while (j > 1) {
            j >>= 1;
            t[i][j] = max(t[i][j << 1], t[i][j << 1 | 1]);
        }
        while (i > 1) {
            j = x + flagx - 1;
            i >>= 1;
            t[i][j] = max(t[i << 1][j], t[i << 1 | 1][j]);
            while (j > 1) {
                j >>= 1;
                t[i][j] = max(t[i][j << 1], t[i][j << 1 | 1]);
            }
        }
    }
    int xquery(int lx, int rx, int ny, int nx = 1, int nl = 1, int nr = flagx) {
        if (nr < lx || rx < nl) return 0;
        if (lx <= nl && nr <= rx) return t[ny][nx];
        int mid = (nl + nr) >> 1;
        return max(xquery(lx, rx, ny, nx << 1, nl, mid), xquery(lx, rx, ny, nx << 1 | 1, mid + 1, nr));
    }
    int yquery(int ly, int ry, int lx, int rx, int ny = 1, int nl = 1, int nr = flagy) {
        if (nr < ly || ry < nl) return 0;
        if (ly <= nl && nr <= ry) return xquery(lx, rx, ny);
        int mid = (nl + nr) >> 1;
        return max(yquery(ly, ry, lx, rx, ny << 1, nl, mid), yquery(ly, ry, lx, rx, ny << 1 | 1, mid + 1, nr));
    }
}seg2d;

int m, n;
int a[MAXM][MAXN];
vector<int> ord;
set<pii> st[MAXN];

void coor_comp(int row) {
    vector<int> cc;
    cc.push_back(-1);
    for (int i = 1; i <= n; i++) {
        cc.push_back(a[row][i]);
    }

    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());
    for (int i = 1; i <= n; i++) {
        a[row][i] = lower_bound(all(cc), a[row][i]) - cc.begin();
    }
}

int subtask13() {
    assert(m == 2);
    seg1d.build(n);
    for (auto& i : ord) {
        int res = seg1d.query(1, a[1][i] - 1);
        seg1d.modify(a[1][i], res + 1);
    }
    return seg1d.query(1, n);
}

int dp[MAXN];
int subtask2() {
    assert(m == 3 && n <= 10'000);
    int ret = 0;
    for (int i = 0; i < sz(ord); i++) {
        int y = a[1][ord[i]], x = a[2][ord[i]];
        int res = 0;
        for (int j = 0; j < i; j++) {
            if (a[1][ord[j]] <= a[1][ord[i]] && a[2][ord[j]] <= a[2][ord[i]])
                res = max(res, dp[ord[j]]);
        }
        dp[ord[i]] = 1 + res;
        ret = max(ret, dp[ord[i]]);
    }
    return ret;
}

int subtask4() {
    assert(m == 3 && n <= 200'000);
    int ret = 0;
    st[0].insert({ -1, -1 });
    for (int i = 0; i < sz(ord); i++) {
        int y = a[1][ord[i]], x = a[2][ord[i]];

        int l = 0, r = i;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            auto it = st[mid].upper_bound({ y, x });
            if (it == st[mid].begin()) r = mid - 1;
            else {
                if (prev(it)->sc < x) l = mid;
                else r = mid - 1;
            }
        }
        
        auto it = st[l + 1].insert({ y, x }).fr;
        it++;
        while (it != st[l + 1].end() && x <= it->sc) {
            auto tmp = it; it++;
            st[l + 1].erase(tmp);
        }

        ret = max(ret, l + 1);
    }
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    coor_comp(0);
    coor_comp(1);
    coor_comp(2);

    ord.resize(n);
    iota(all(ord), 1);
    sort(all(ord), [&](int p1, int p2) {
        return a[0][p1] < a[0][p2];
    });

    if (m == 2) cout << subtask13();
    else if (n <= 10'000) cout << subtask2();
    else cout << subtask4();
}
