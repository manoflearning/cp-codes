#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int n;
ll k;
vector<ll> a, b;

struct Node {
    ll rem_b, rem_a;
    Node operator+(const Node &rhs) const {
        Node ret;
        ret.rem_b = rem_b + max(0ll, rhs.rem_b - rem_a);
        ret.rem_a = max(0ll, rem_a - rhs.rem_b) + rhs.rem_a;
        return ret;
    }
};

int flag;    // array size
struct Seg { // 1-indexed
  vector<Node> t;
  void build() {
    t.clear();
    for (flag = 1; flag < 2 * n; flag <<= 1);
    t.resize(2 * flag);
    for (int i = flag; i < flag + 2 * n; i++) {
        t[i].rem_b = max(0ll, b[(i - flag) % n] - a[(i - flag) % n]);
        t[i].rem_a = max(0ll, a[(i - flag) % n] - b[(i - flag) % n]);
    }
    for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
  }
  Node query(int l, int r, int n = 1, int nl = 1, int nr = flag) { // sum on interval [l, r]
    if (r < nl || nr < l) return {0, 0};
    if (l <= nl && nr <= r) return t[n];
    int mid = (nl + nr) / 2;
    return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
  }
} seg;

void init() {}

void input() {
    cin >> n >> k;
    a.resize(n);
    b.resize(n);
    for (auto &i : a) cin >> i;
    for (auto &i : b) cin >> i;
}

bool f(int x) {
    __int128_t rem_k = (__int128_t)k * x;
    for (int i = 0; i < n; i++) {
        ll rem_a = max(0ll, a[i] - (seg.query(i + 2, i + x).rem_b + b[i]));
        if (rem_a > k) return 0;
        rem_k -= rem_a;
    }
    return rem_k >= 0;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    int tc; cin >> tc;
    while (tc--) {
        init();

        input();

        ll sum_a = 0;
        for (auto &i : a) sum_a += i;
        if (sum_a == k) {
            cout << 0 << '\n';
            continue;
        }

        seg.build();

        int l = 1, r = n;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (f(mid)) r = mid;
            else l = mid + 1;
        }
        cout << l << '\n';
    }
}
