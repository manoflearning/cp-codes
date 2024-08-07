//#pragma GCC optimize("O3")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fr first
#define sc second
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int flag;  // array size
struct Seg {  // 1-indexed
    vector<ll> t;
    void build(int n) {
        for (flag = 1; flag < n; flag <<= 1);
        t.resize(2 * flag);
    }
    void modify(int p, ll value) {  // set value at position p
        for (t[p += flag - 1] += value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
    }
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return t[n];
        int mid = (nl + nr) / 2;
        return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
    }
}seg;

ll n, m;
vector<int> a[10101];
ll ans = 0;

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        a[i].resize(m);
        for (auto& j : a[i]) cin >> j;
    }
}

void sortAndCompress() {
    vector<int> cc(1, 0);
    for (int i = 1; i <= n; i++) {
        sort(a[i].begin(), a[i].end());
        for (auto& j : a[i]) cc.push_back(j);
    }

    sort(cc.begin(), cc.end());

    for (int i = 1; i <= n; i++) {
        for (auto& j : a[i])
            j = lower_bound(cc.begin(), cc.end(), j) - cc.begin();
    }

    seg.build(sz(cc));
}

void solve1() {
    for (int i = 1; i <= n; i++) {
        ans += 1 * m * (n - i);
        ans += (m - 1) * m / 2 * (n - i);
    }
}

void solve2() {
    for (auto& j : a[n])
        seg.modify(j, 1);
    for (int i = n - 1; i >= 1; i--) {
        for (auto& j : a[i]) {
            ans += seg.query(1, j - 1);
        }
        for (auto& j : a[i])
            seg.modify(j, 1);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

	input();

    sortAndCompress();

    solve1();
    solve2();

    cout << ans;
}