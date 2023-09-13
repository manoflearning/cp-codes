#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll, ll>
#define fr first
#define sc second

const int MAXN = 505050;
const ll INF = 1e18;

int n;
ll p, a[MAXN];

void input() {
    cin >> n >> p;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

int st[MAXN];
void getStartIndex() {
    priority_queue<pll> pq;
    st[1] = 1;
    pq.push({ a[1], -1 });
    for (int i = 2; i <= n; i++) {
        st[i] = st[i - 1];
        pq.push({ a[i], -i });
        while (1) {
            ll x = pq.top().fr, y = -pq.top().sc;
            if (y < st[i]) { pq.pop(); continue; }
            if (p - (i - st[i]) >= x) break;
            while (p - (i - st[i]) < x) st[i]++;
        }
    }
}

int flag;
struct Seg {
    const pll e = { INF, INF };
    vector<pll> t, lazy;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1, e);
        lazy.resize(flag << 1, e);
    }
    void modify(int l, int r, pll val, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);
        if (r < nl || nr < l) return;
        if (l <= nl && nr <= r) {
            lazy[n] = val;
            propagate(n);
            return;
        }
        int mid = (nl + nr) >> 1;
        modify(l, r, val, n << 1, nl, mid);
        modify(l, r, val, n << 1 | 1, mid + 1, nr);
        if (t[n << 1].fr + t[n << 1].sc <= t[n << 1 | 1].fr + t[n << 1 | 1].sc) t[n] = t[n << 1];
        else t[n] = t[n << 1 | 1];
        cout << nl << ' ' << nr << ' ' << t[n].fr + t[n].sc << '\n';
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        propagate(n);
        if (r < nl || nr < l) return INF;
        if (l <= nl && nr <= r) return t[n].fr + t[n].sc;
        int mid = (nl + nr) >> 1;
        return min(query(l, r, n << 1, nl, mid), 
        query(l, r, n << 1 | 1, mid + 1, nr));
    }
    void propagate(int n) {
        if (lazy[n] == e) return;
        if (n < flag) {
            lazy[n << 1].fr += lazy[n].fr;
            lazy[n << 1].sc = max(lazy[n << 1].sc, lazy[n].sc);
            lazy[n << 1 | 1].fr += lazy[n].fr;
            lazy[n << 1 | 1].sc = max(lazy[n << 1 | 1].sc, lazy[n].sc);
        }
        if (t[n] == e) t[n] = { 0, 0 };
        t[n].fr += lazy[n].fr;
        t[n].sc = max(t[n].sc, lazy[n].sc);
        lazy[n] = e;
    }
}seg;

ll dp[MAXN];
void f() {
    seg.build(MAXN);
    seg.modify(1, 1, { 0, 0 });
    for (int i = 1; i <= n; i++) {
        seg.modify(1, i - 1, { 1, 0 });
        seg.modify(1, i, { 0, a[i] });
        dp[i] = seg.query(st[i], i);
        for (int j = st[i]; j <= i; j++)
            cout << seg.query(j, j) << ' ';
        cout << seg.query(st[i], i) << '\n';
        cout << dp[i] << '\n';
        seg.modify(i + 1, i + 1, { dp[i], 0 });
    }
}
void naive() {
    dp[1] = a[1];
    for (int i = 2; i <= n; i++) {
        ll mx = a[i];
        dp[i] = mx + dp[i - 1];
        for (int j = i - 1; j >= 1; j--) {
            mx = max(mx, a[j]);
            if (mx > p - (i - j)) break;
            dp[i] = min(dp[i], i - j + mx + dp[j - 1]);
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    getStartIndex();

    // naive();

    f();

    cout << dp[n];
}