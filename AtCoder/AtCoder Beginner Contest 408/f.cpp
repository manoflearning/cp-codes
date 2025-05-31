#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

const int N = 505050;

int flag;    // array size
struct Seg { // 1-indexed
  vector<ll> t;
  void build(int n) {
    for (flag = 1; flag < n; flag <<= 1);
    t.resize(2 * flag, -1);
  }
  void modify(int p, ll value) { // set value at position p
    for (t[p += flag - 1] = value; p > 1; p >>= 1)
        t[p >> 1] = max(t[p], t[p ^ 1]);
  }
  ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) { // sum on interval [l, r]
    if (r < nl || nr < l) return -1;
    if (l <= nl && nr <= r) return t[n];
    int mid = (nl + nr) / 2;
    return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
  }
} seg;

int n, d, r;
int h[N], dp[N];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> d >> r;
    for (int i = 1; i <= n; i++) cin >> h[i];

    seg.build(n);

    vector<int> ord(n);
    iota(all(ord), 1);
    sort(all(ord), [&](int p1, int p2) {
        return h[p1] < h[p2];
    });

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (i >= d) {
            int prv = ord[i - d];
            seg.modify(prv, dp[prv]);
        }

        int now = ord[i];
        dp[now] = 1 + seg.query(max(1, now - r), min(n, now + r));

        ans = max(ans, dp[now]);
    }

    cout << ans;
}
