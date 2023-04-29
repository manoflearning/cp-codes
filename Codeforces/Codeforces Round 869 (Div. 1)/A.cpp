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
		//for (int i = flag; i < flag + n; i++) cin >> t[i];
		//for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
	}
}seg;

//struct Q { int l, r, idx; };

int n, m;
int a[202020], vi[202020];//, mx[202020];
//vector<Q> q;
//vector<int> ans;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];

    for (int i = 2; i < n; i++)
        if (a[i - 1] >= a[i] && a[i] >= a[i + 1]) vi[i] = 1;
    
    vector<int> arr(1, 1);
    for (int i = 1; i <= n; i++) {
        if (vi[i]) arr.push_back(i);
    }
    arr.push_back(n);

    seg.build(sz(arr));

    vector<int> mx(sz(arr));
    for (int i = 1; i + 1 < sz(mx); i++) {
        mx[i] = arr[i + 1] - arr[i] + 1;
        seg.modify(i, mx[i]);
    }

    while (m--) {
        int l, r;
        cin >> l >> r;
        int s = upper_bound(all(arr), l) - arr.begin();
        int e = lower_bound(all(arr), r) - arr.begin() - 1;
        //cout << l << ' ' << r << ' ' << s << ' ' << e << '\n';
        if (e < s) {
            cout << r - l + 1 << '\n';
        }
        else {
            cout << (r - l + 1) - (e - s + 1) << '\n';
            /*int ans = seg.query(s, e - 1);
            ans = max(ans, r - arr[e] + 1);
            ans = max(ans, arr[s] - l + 1);
            cout << ans << '\n';*/
        }
    }

    /*int len = 0;
    for (int i = n; i >= 1; i--) {
        len++;
        mx[i] = len;
        if (vi[i]) len = 1;
    }

    seg.build(n);

    q.resize(m);
    ans.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> q[i].l >> q[i].r;
        q[i].idx = i;
    }

    sort(q.begin(), q.end(), [&](const Q& p1, const Q& p2) {
        return p1.r < p2.r;
    });

    vector<int> arr;
    int prv = 1;
    for (auto& i : q) {
        while (prv <= i.r) {
            if (vi[prv]) arr.push_back(prv);
        }
    }*/

	return 0;
}