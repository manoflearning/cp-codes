// rem[i] = max(0, rem[i - 1] + a[i] - b[i])

// ans := sum(a[i]) - rem[n]

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

const int MAXN = 505050;

int flag;  // array size
struct Seg {  // 1-indexed
	vector<ll> t, lazy;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
		lazy.resize(2 * flag);
	}
	// add a value to all elements in interval [l, r]
	void modify(int l, int r, ll value, int n = 1, int nl = 1, int nr = flag) {
		propagate(n);
		if (r < nl || nr < l) return;
		if (l <= nl && nr <= r) {
			lazy[n] += value;
			propagate(n);
			return;
		}
		int mid = (nl + nr) >> 1;
		modify(l, r, value, n << 1, nl, mid);
		modify(l, r, value, n << 1 | 1, mid + 1, nr);
		t[n] = t[n << 1] + t[n << 1 | 1];
	}
    ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		propagate(n);
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
	}
    ll kth(ll k, int n = 1) {  // sum on interval [l, r]
        if (n < flag) return n - flag + 1;

		propagate(n);
        propagate(n << 1);
        propagate(n << 1 | 1);

		if (k <= t[n << 1]) return kth(k, n << 1);
        else return kth(k - t[n << 1], n << 1 | 1);
	}
	void propagate(int n) {
		if (lazy[n] != 0) {
			if (n < flag) {
                // left
                ll tmp = max(lazy[n], -(t[n << 1] + lazy[n << 1]));
				lazy[n << 1] += tmp;
                // right
                tmp = lazy[n] - tmp;
				lazy[n << 1 | 1] += tmp;
                assert(lazy[n << 1] <= t[n << 1]);
                assert(lazy[n << 1 | 1] <= t[n << 1 | 1]);
			}
			t[n] += lazy[n];
			lazy[n] = 0;
		}
	}
}seg;

int n, q;
ll a[MAXN], rem[MAXN], b[MAXN], c[MAXN];
ll allb = 0;

void input() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i <= n - 1; i++) cin >> c[i];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    for (int i = 1; i <= n - 1; i++) cin >> c[i];

    seg.build(n + 1);
    for (int i = 1; i <= n; i++) {
        allb += b[i];
        
        rem[i] = a[i] + rem[i - 1];
        if (rem[i] < b[i]) seg.modify(i, i, b[i] - rem[i]);
        rem[i] = max(0ll, rem[i] - b[i]);
    }

    while (q--) {
        ll p, x, y, z;
        cin >> p >> x >> y >> z;

        ll diffa = a[p] - x;
        if (diffa > 0) {
            seg.modify(p, n + 1, -diffa);
        }
        if (diffa < 0) {

        }

        ll diffb = b[p] - x;
        if (b[p] < x) {
            seg.modify(p, p, x - b[p]);
        }
        if (b[p] > x) {
            
        }

        // allb -= b[p];
        // allb += y;
        // b[p] = y;

        cout << allb - seg.query(1, n) << '\n';
    }
}