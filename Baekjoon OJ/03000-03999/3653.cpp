#include <bits/stdc++.h>
using namespace std;

int flag;
struct Seg {
    vector<int> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void add(int p, int val) {
        for (t[p += flag - 1] += val; p > 1; p >>= 1)
            t[p >> 1] = t[p] + t[p ^ 1];
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
}seg;

int n, m;
int a[101010], Hash[101010];

void init() {
    seg.t.clear();
}

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) Hash[i] = n - i + 1;
    for (int i = 1; i <= m; i++) cin >> a[i];
}

void solve() {
    seg.build(n + m);
    for (int i = 1; i <= n; i++) {
        seg.add(Hash[i], 1);
    }

    for (int i = 1; i <= m; i++) {
        int x = a[i];
        cout << seg.query(Hash[x] + 1, n + m) << ' ';
        seg.add(Hash[x], -1);
        Hash[x] = n + i;
        seg.add(Hash[x], 1);
    }
    cout << '\n';
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        solve();
    }
}