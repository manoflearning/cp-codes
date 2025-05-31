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
vector<ll> ssum;

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
    if (r < nl || nr < l) return {0};
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

ll sum(int l, int r) {
    if (r >= l) return ssum[r] - (l > 0 ? ssum[l - 1] : 0);
    else return (ssum[n - 1] - ssum[l - 1]) + ssum[r];
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

        seg.build();

        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (b[i] >= a[i]) {
                ans = max(ans, 1);
            } else {
                int l = 2, r = n;
                while (l < r) {
                    int mid = (l + r) >> 1;
                    if (seg.query(i + 2, i + mid).rem_b + b[i] >= a[i]) r = mid;
                    else l = mid + 1;
                }
                ans = max(ans, l);
            }
        }

        cout << ans << '\n';
    }
}
