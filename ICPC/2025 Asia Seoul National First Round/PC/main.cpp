#include <bits/stdc++.h>
using namespace std;

const int N = 252525;
const int INF = 1e9 + 7;

int flag;
struct Seg {
    vector<int> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1, INF);
    }
    void modify(int p, int val) {
        for (t[p += flag - 1] = val; p > 1; p >>= 1) {
            t[p >> 1] = min(t[p], t[p ^ 1]);
        }
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (r < nl || nr < l) return INF;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
    }
} seg;

int n, a[N];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
    freopen("../output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    seg.build(n);

    int ans = 0;
    for (int i = n; i >= 1; i--) {
        int x = seg.query(1, a[i] - 1);
        int y = seg.query(a[i] + 1, n);

        if (x != INF && i + 1 < x) ans++;
        if (y != INF && i + 1 < y) ans++;

        seg.modify(a[i], i);
    }

    cout << ans;
}
