#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 202020;

int flag;    // array size
struct Seg { // 1-indexed
    vector<ll> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(2 * flag);
    }
    void modify(int p, ll value) { // set value at position p
        for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]);
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) { // sum on interval [l, r]
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) / 2;
        return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
} seg0, seg1;

int n, a[N], b[N];
vector<int> ord;
int dp[N][2];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        if (a[i] > b[i]) swap(a[i], b[i]);
    }

    ord.resize(n);
    iota(all(ord), 1);

    sort(all(ord), [&](int p1, int p2) {
        return a[p1] > a[p2];
    });
    seg0.build(2 * n);
    for (auto i : ord) {
        dp[i][0] = 1 + seg0.query(a[i] + 1, b[i] - 1);
        seg0.modify(b[i], dp[i][0]);
    }

    sort(all(ord), [&](int p1, int p2) {
        return a[p1] < a[p2];
    });
    seg1.build(2 * n);
    for (auto i : ord) {
        int prv0to1 = seg0.query(1, a[i] - 1);
        int prv1 = seg1.query(b[i] + 1, 2 * n);
        dp[i][1] = 1 + max(prv0to1, prv1);
        seg1.modify(b[i], dp[i][1]);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, dp[i][1]);
    }

    cout << ans;
}
