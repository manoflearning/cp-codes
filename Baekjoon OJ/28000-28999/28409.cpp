#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int INF = 1e9 + 7;

int flag;
struct Seg {
    const pll e = { INF, INF };
    vector<pll> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1, e);
    }
    void modify(int p, pll val) {
        for (t[p += flag - 1] = val; p > 1; p >>= 1)
            t[p >> 1] = min(t[p], t[p ^ 1]);
    }
    pll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return e;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
}seg;

int n, m, mxx;
vector<pll> a, b;
ll dr[404040];
int ans[202020];

void input() {
    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i.fr >> i.sc;
    cin >> m;
    b.resize(m);
    for (auto& i : b) cin >> i.fr >> i.sc;
}

void buildCoor() {
    for (int i = 1; i < n; i++) a[i].fr += a[i - 1].fr;
    for (int i = 1; i < m; i++) b[i].fr += b[i - 1].fr;
}

void cc() {
    vector<ll> c(1, -1);
    for (auto& i : a) c.push_back(i.fr);
    for (auto& i : b) c.push_back(i.fr);
    sort(all(c));
    c.erase(unique(all(c)), c.end());
    for (auto& i : a) {
        i.fr = lower_bound(all(c), i.fr) - c.begin();
    }
    for (auto& i : b) {
        i.fr = lower_bound(all(c), i.fr) - c.begin();
    }
    mxx = sz(c) - 1;
}

void buildSeg() {
    seg.build(mxx);
    for (int x = 1; x <= a[0].fr; x++) seg.modify(x, { a[0].sc, 0 });
    for (int i = 1; i < n; i++) {
        for (int x = a[i - 1].fr + 1; x <= a[i].fr; x++) {
            seg.modify(x, { a[i].sc, i });
        }
    }
}

void minCount() {
    for (int i = 0; i < m; i++) {
        int isTop = 1;
        if (0 <= i - 1 && b[i - 1].sc > b[i].sc) isTop = 0;
        if (i + 1 < m && b[i].sc < b[i + 1].sc) isTop = 0;

        if (!isTop) continue;

        pll mn = seg.query(i == 0 ? 1 : b[i - 1].fr + 1, b[i].fr);
        if (mn.fr == b[i].sc) ans[mn.sc] = 1;
    }
}

void drawing() {
    ll hei = 0;
    for (int i = 0; i < n; i++) {
        if (ans[i]) hei = a[i].sc;
        else hei = min(hei, a[i].sc);
        for (int x = (i == 0 ? 1 : a[i - 1].fr + 1); x <= a[i].fr; x++) {
            dr[x] = max(dr[x], hei);
        }
    }
    hei = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (ans[i]) hei = a[i].sc;
        else hei = min(hei, a[i].sc);
        for (int x = (i == 0 ? 1 : a[i - 1].fr + 1); x <= a[i].fr; x++) {
            dr[x] = max(dr[x], hei);
        }
    }
}

bool isValid() {
    for (int x = 1; x <= b[0].fr; x++) {
        if (dr[x] != b[0].sc) return 0;
    }
    for (int i = 1; i < m; i++) {
        for (int x = b[i - 1].fr + 1; x <= b[i].fr; x++) {
            if (dr[x] != b[i].sc) return 0;
        }
    }
    return 1;
}

void printAns() {
    int sum = 0;
    for (int i = 0; i < 202020; i++) sum += ans[i];

    cout << sum << '\n';
    for (int i = 0; i < 202020; i++) 
        if (ans[i]) cout << i + 1 << ' ';
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    buildCoor();

    cc();

    buildSeg();

    minCount();

    drawing();    

    if (isValid()) printAns();
    else cout << -1;
}