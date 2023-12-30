// p = [1 3 2]
// reachable:
// [1], [1, 2], [1, 3, 2]
// non-reachable:
// [3], [2], [1, 3], [3, 2]

// p = { 2, 4, 1, 3 }
// f(1, 4) = 

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
const int MOD = 998'244'353;
const int dy[] = { 0, 0, 1, -1, 1, 1, -1, -1 };
const int dx[] = { 1, -1, 0, 0, 1, -1, 1, -1 };

int n;
vector<int> p;
int rp[303003];

void init() {

}

void input() {
    cin >> n;
    p.resize(n);
    for (auto& i : p) cin >> i;
}

void cc() {
    vector<int> c = p;
    c.push_back(-1);
    sort(all(c));
    c.erase(unique(all(c)), c.end());
    for (auto& i : p) {
        i = lower_bound(all(c), i) - c.begin();
    }
}

int flag;  // array size
struct Seg {  // 1-indexed
	vector<ll> t;
	void build(int n) {
        t.clear();
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(2 * flag, INF);
		// for (int i = flag; i < flag + n; i++) cin >> t[i];
		// for (int i = flag - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += flag - 1] = value; p > 1; p >>= 1) 
        t[p >> 1] = min(t[p], t[p ^ 1]);
	}
	ll query(int l, int r, int n = 1, int nl = 1, int nr = flag) {  // sum on interval [l, r]
		if (r < nl || nr < l) return INF;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) / 2;
		return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}seg;

ll f(int l, int r) {
    if (l == r) return 1;
    if (l > r) return 0;

    int mn = seg.query(l + 1, r + 1), mnLoc = rp[mn];
    return (f(l, mnLoc - 1) + 1) * (f(mnLoc + 1, r) + 1) % MOD;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int tc; cin >> tc;
    for (int tt = 1; tt <= tc; tt++) {
        init();

        input();

        cc();

        seg.build(n);
        for (int i = 0; i < n; i++) {
            seg.modify(i + 1, p[i]);
            rp[p[i]] = i;
        }

        cout << f(0, n - 1) << '\n';
    }
}