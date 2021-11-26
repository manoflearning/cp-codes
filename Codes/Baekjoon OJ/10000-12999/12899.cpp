#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

const int MAXN = 2e6;  // limit for array size

struct Seg {
	int flag;  // array size
	vector<ll> t;

	void build(int N) {
		for (flag = 1; flag < N; flag <<= 1);
		t.resize(2 * flag);
	}
	void modify(int p, int val) {  // set value at position p
		for (t[p += flag - 1] += val; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
	}
	ll query(int val) {
		return query(1, 1, flag, val);
	}
	ll query(int n, int nl, int nr, int val) {  // sum on interval [l, r]
		if (nl == nr) {
		    modify(nl, -1);
		    return nl;
		}

		int mid = (nl + nr) / 2;
		if (t[n << 1] >= val) return query(n << 1, nl, mid, val);
		else return query(n << 1 | 1, mid + 1, nr, val - t[n << 1]);
	}
}seg;

void init() {
    seg.build((int)2e6);
}

void procedure() {
    int n; cin >> n;
	
	while (n--) {
	    int t, x;
	    cin >> t >> x;
	    
	    if (t == 1) seg.modify(x, 1);
	    if (t == 2) cout << seg.query(x) << '\n';
	}
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	init();
	
	procedure();
	
	return 0;
}
