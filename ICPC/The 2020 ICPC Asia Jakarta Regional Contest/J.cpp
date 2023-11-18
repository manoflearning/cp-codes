#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int INF = 1e9 + 7;

ll gcd(ll x, ll y) {
    if (!y) return x;
    else return gcd(y, x % y);
}

int flag;  // array size
struct SegMax {  // 1-indexed
	vector<ll> t;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag, 0);
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += flag - 1] = value; p > 1; p >>= 1) 
            t[p >> 1] = max(t[p], t[p ^ 1]);
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) >> 1;
		return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}segmax, segequal;

struct SegMin {  // 1-indexed
	vector<ll> t;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag, INF);
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += flag - 1] = value; p > 1; p >>= 1) 
            t[p >> 1] = min(t[p], t[p ^ 1]);
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
		if (r < nl || nr < l) return INF;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) >> 1;
		return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}segmin;

struct SegGcd {  // 1-indexed
	vector<ll> t;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag, 0);
	}
	void modify(int p, ll value) {  // set value at position p
        if (value < 0) value = -value;
		for (t[p += flag - 1] = value; p > 1; p >>= 1) 
            t[p >> 1] = gcd(t[p], t[p ^ 1]);
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) >> 1;
		return gcd(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}seggcd;

int n, q;
int a[101010], closestEqual[101010];
map<int, set<int>> equals;

void YES() { cout << "YES" << '\n'; }
void NO() { cout << "NO" << '\n'; }

void input() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
}

void buildSegmentTrees() {
    segmax.build(n);
    segmin.build(n);
    segequal.build(n);
    seggcd.build(n);

    for (int i = 1; i <= n; i++) {
        segmax.modify(i, a[i]);
        segmin.modify(i, a[i]);

        if (!equals[a[i]].empty()) {
            closestEqual[i] = *equals[a[i]].rbegin();
        }
        equals[a[i]].insert(i);
        segequal.modify(i, closestEqual[i]);

        if (i < n) seggcd.modify(i, a[i + 1] - a[i]);
    }
}

void modifyEqual(set<int>& equal, int mid) {
    auto it = equal.lower_bound(mid);
    if (it == equal.end()) return;
    int idx = *it;
    
    if (it == equal.begin()) closestEqual[idx] = 0;
    else {
        --it;
        closestEqual[idx] = *it;
    }
    segequal.modify(idx, closestEqual[idx]);
}

void solve() {
    while (q--) {
        int op, x, y;
        cin >> op >> x >> y;

        if (op == 1) {
            int tmp = a[x];
            a[x] = y;

            segmax.modify(x, a[x]);
            segmin.modify(x, a[x]);

            set<int>& oldEqual = equals[tmp];
            set<int>& newEqual = equals[a[x]];

            oldEqual.erase(x);
            newEqual.insert(x);
            
            modifyEqual(oldEqual, x + 1);
            modifyEqual(newEqual, x);
            modifyEqual(newEqual, x + 1);

            if (1 < x) seggcd.modify(x - 1, a[x] - a[x - 1]);
            if (x < n) seggcd.modify(x, a[x + 1] - a[x]);
        }
        if (op == 2) {
            ll delta = segmax.query(x, y) - segmin.query(x, y);
            ll len = y - x;
            ll g = seggcd.query(x, y - 1);
            
            if (delta == 0) YES();
            else {
                if (delta != g * len) NO();
                else if (segequal.query(x, y) >= x) NO();
                else YES();
            }
        }
    }
}

int main() {
    #ifndef ONLNE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    buildSegmentTrees();

    solve();
}