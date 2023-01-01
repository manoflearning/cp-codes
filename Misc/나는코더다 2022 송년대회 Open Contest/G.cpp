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
#define vt vector
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

const double EPS = 1e-9;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

ll psum[101010];
int lb;

int flag;  // array size
struct Seg {  // 1-indexed
    struct Node {
        ll val; int idx;
        bool operator<(const Node& rhs) const {
            if (idx < rhs.idx) {
                return (val - psum[lb]) * (rhs.idx - idx) < (rhs.val - val) * (idx - lb);
            }
            else {
                return (val - rhs.val) * (rhs.idx - lb) < (rhs.val - psum[lb]) * (idx - rhs.idx);
            }
        }
    };
	vector<Node> t;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
		//for (int i = flag; i < flag + n; i++) cin >> t[i];
		//for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int p, ll value) {  // set value at position p
        t[p + flag - 1] = { value, p };
        p += flag - 1;
		for (; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]);
	}
	Node query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return { 0, 100 };
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}seg;

int n, q;
ll a[101010];

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        psum[i] = a[i] + psum[i - 1];
    }

	seg.build(n);
    for (int i = 1; i <= n; i++) {
        seg.modify(i, psum[i]);
    }

    while (q--) {
        int s1, e1, s2, e2;
        cin >> s1 >> e1 >> s2 >> e2;

        lb = 0;
        int res1 = seg.query(s1, e1).idx;
        lb = res1;
        int res2 = seg.query(s2, e2).idx;
        cout << res1 << ' ' << res2 << '\n';
        cout << (psum[res2] - psum[res1 - 1]) / (res2 - res1 + 1) << '\n';
    }

	return 0;
}