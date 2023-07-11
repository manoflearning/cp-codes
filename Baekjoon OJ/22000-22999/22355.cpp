// 최적해는 나중 말뚝 높이를 x라 할 때, x = H_i 중에 존재한다.
#include <bits/stdc++.h>
using namespace std;
#define ll long long

int flag;
struct Seg {
    vector<ll> t, lazy;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(flag << 1);
        lazy.resize(flag << 1);
    }
    void addA(int l, int r, int val, int n = 1, int nl = 1, int nr = flag) {

    }
    void addB(int l, int r, int val, int n = 1, int nl = 1, int nr = flag) {

    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {

    }
    void propagate(int n, int l, int r, int nl, int nr) {
        if (!lazy[n]) return;
        if (n < flag) {
            lazy[n << 1] += lazy[n];
            lazy[n << 1 | 1] += lazy[n];
        }
        t[n] += ((nr - l + 1) + (nl - l + 1)) * (nr - nl + 1) / 2;
    }
}seg;

int n, k;
ll h[101010], a[101010], b[101010];

void input() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> h[i];
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    seg.build(101010);
    for (int i = 1; i <= k; i++) {
        seg.addA(1, h[i] - 1, a[i]);
        seg.addB(h[i] + 1, 101010, b[i]);
    }

    ll ans = seg.query(1, 101010);
    for (int i = 2; i <= n - k + 1; i++) {
        seg.addA(1, h[i - 1] - 1, -a[i - 1]);
        seg.addB(h[i - 1] + 1, 101010, -b[i - 1]);

        seg.addA(1, h[i + k] - 1, a[i + k]);
        seg.addB(h[i + k] + 1, 101010, b[i + k]);

        ans = min(ans, seg.query(1, 101010));
    }

    cout << ans;
}