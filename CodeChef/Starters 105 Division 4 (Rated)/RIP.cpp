// #pragma GCC optimize("O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")

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

int n, m;
int a[101010], b[101010], c[101010];
vector<int> isInC;
ll ans = 0;

int flag;  // array size
struct Seg {  // 1-indexed
	vector<ll> t;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]);
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}seg;

void init() {}

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i <= m; i++) cin >> c[i];
    isInC.resize(n + 1);
    for (int i = 1; i <= m; i++) isInC[c[i]] = i;
}

void solve() {
    vector<int> arr1, arr2;
    for (int i = 1; i <= n; i++) {
        if (isInC[i]) arr2.push_back(i);
        else arr1.push_back(i);
        ans += b[i];
    }

    sort(all(arr1), [&](int p1, int p2) {
        return a[p1] ^ a[p2] ? a[p1] > a[p2] : b[p1] < b[p2];
    });
    sort(all(arr2), [&](int p1, int p2) {
        return isInC[p1] < isInC[p2];
    });

    for (int i = 0; i < sz(arr2); i++) {
        int val = a[arr2[i]];
        
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/input.txt", "r", stdin);
    freopen("/Users/jeongwoo-kyung/programming/cp-codes/output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        init();

        input();

        solve();

        cout << ans << '\n';
    }
}