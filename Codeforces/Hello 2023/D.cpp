// solution 2: using divide and conquer & segment tree
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

int flag;  // array size
struct Seg {  // 1-indexed
	vector<ll> t;
	void build(int n) {
		t.clear();
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag);
		//for (int i = flag; i < flag + n; i++) cin >> t[i];
		//for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += flag - 1] = value; p > 1; p >>= 1) 
			t[p >> 1] = max(t[p], t[p ^ 1]);
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}seg;

int n, m;
ll a[202020], b[202020], x[202020];
map<ll, vector<int>> idx;
map<ll, int> cnt;
int ans = 1;

void init() {
	idx.clear();
	cnt.clear();
	ans = 1;
}

void input() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	cin >> m;
	for (int i = 1; i <= m; i++) cin >> x[i];
}

bool BbiggerthanA() {
	for (int i = 1; i <= n; i++) {
		if (a[i] < b[i]) return 1;
	}
	return 0;
}

void f(int l, int r) {
	if (l > r) return;

	ll mx = seg.query(l, r);

	int used = 0;
	auto& arr = idx[mx];

	int lb = lower_bound(all(arr), l) - arr.begin();
	int rb = upper_bound(all(arr), r) - arr.begin();
	int prv = l;
	for (int i = lb; i < rb; i++) {
		int v = arr[i];
		if (a[v] > b[v]) used = 1;

		f(prv, v - 1);
		prv = v + 1;
	}
	f(prv, r);

	if (used) {
		cnt[mx]--;
		if (cnt[mx] < 0) ans = 0;
	}
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
	for (int tt = 1; tt <= tc; tt++) {
		init();

		input();

		if (BbiggerthanA()) {
			cout << "NO\n";
			continue;
		}

		seg.build(n);

		for (int i = 1; i <= n; i++) {
			idx[b[i]].push_back(i);
			seg.modify(i, b[i]);
		}
		for (int i = 1; i <= m; i++) cnt[x[i]]++;

		f(1, n);
		cout << (ans ? "YES" : "NO") << '\n';
	}

	return 0;
}

// solution 1: using monotone stack
/*#include <bits/stdc++.h>
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

int n, m;
ll a[202020], b[202020], x[202020];
map<ll, int> cnt;

void input() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];
	cin >> m;
	for (int i = 1; i <= m; i++) cin >> x[i];
}

bool BbiggerthanA() {
	for (int i = 1; i <= n; i++) {
		if (a[i] < b[i]) return 1;
	}
	return 0;
}

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int tc; cin >> tc;
	for (int tt = 1; tt <= tc; tt++) {
		input();

		if (BbiggerthanA()) {
			cout << "NO\n";
			continue;
		}

		for (int i = 1; i <= m; i++) cnt[x[i]]++;

		stack<int> stk;
		for (int i = 1; i <= n; i++) {
			while (sz(stk) && stk.top() < b[i]) stk.pop();

			if (sz(stk) && stk.top() == b[i]) continue;
			if (a[i] == b[i]) continue;
			
			stk.push(b[i]);
			cnt[b[i]]--;
		}

		int ans = 1;
		for (auto& i : cnt)
			if (i.sc < 0) ans = 0;

		cout << (ans ? "YES" : "NO") << '\n';

		// init
		cnt.clear();
	}

	return 0;
}*/