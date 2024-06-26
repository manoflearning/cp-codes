#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()

int flag;
struct Seg {
    vector<int> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
    }
    void modify(int p) {
        for (t[p += flag - 1]++; p > 1; p >>= 1)
            t[p >> 1] = t[p] + t[p ^ 1];
    }
    int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) >> 1;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
}seg;

int n;
vector<int> a;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    a.resize(n);
    for (auto& i : a) cin >> i;

    vector<int> c = a;
    c.push_back(-1);
    sort(all(c));
    c.erase(unique(all(c)), c.end());
    for (auto& i : a) i = lower_bound(all(c), i) - c.begin();

    seg.build(n);
    int ans = 0;
    for (auto& i : a) {
        ans = max(ans, seg.query(i + 1, n));
        seg.modify(i);
    }
    cout << ans + 1;
}