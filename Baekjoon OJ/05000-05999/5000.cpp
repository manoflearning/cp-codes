#include <bits/stdc++.h>
using namespace std;
#define ll long long

int flag;
struct Seg {
    vector<ll> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    } 
    void init() {
        t.clear();
        t.resize(flag << 1);
    }
    void modify(int p) {
        for (t[p += flag - 1]++; p > 1; p >>= 1)
            t[p >> 1] = t[p] + t[p ^ 1];
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
}seg;

int n, a[101010], b[101010];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    seg.build(n);
    ll res1 = 0, res2 = 0;
    for (int i = 1; i <= n; i++) {
        res1 += seg.query(a[i] + 1, n);
        seg.modify(a[i]);
    }
    seg.init();
    for (int i = 1; i <= n; i++) {
        res2 += seg.query(b[i] + 1, n);
        seg.modify(b[i]);
    }

    cout << ((res1 & 1) == (res2 & 1) ? "Possible" : "Impossible");
}