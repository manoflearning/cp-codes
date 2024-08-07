#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <cassert>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vi vector<int>
#define vvi vector<vector<int>>
#define vl vector<ll>
#define vvl vector<vector<ll>>

const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const int dy[] = { 0, 0, 1, -1 };
const int dx[] = { 1, -1, 0, 0 };

struct mnmx {
    ll mn, mx;
};

struct Seg {
	int flag;  // array size
	vector<mnmx> t;
    
    mnmx cal(mnmx a, mnmx b) {
        return { min(a.mn, b.mn), max(a.mx, b.mx) };
    }
	void build(int N) {
		for (flag = 1; flag < N; flag <<= 1);
		t.resize(2 * flag);

		for (int i = flag; i < flag + N; i++) t[i] = { i - flag + 1, i - flag + 1 };
		for (int i = flag + N; i < 2 * flag; i++) t[i] = { INF, -1 };
		for (int i = flag - 1; i >= 1; i--) t[i] = cal(t[i << 1], t[i << 1 | 1]);
	}
	void modify(int p, ll val) {  // set value at position p
		for (t[p += flag - 1] = { val, val }; p > 1; p >>= 1) t[p >> 1] = cal(t[p], t[p ^ 1]);
	}
	mnmx query(int l, int r) {
		return query(l, r, 1, 1, flag);
	}
	mnmx query(int l, int r, int n, int nl, int nr) {  // sum on interval [l, r]
		if (r < nl || nr < l) return { INF, -1 };
		if (l <= nl && nr <= r) return t[n];

		int mid = (nl + nr) / 2;
		return cal(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}seg;

int n, k;

void init() {
    seg.t.clear();
}

void input() {
    cin >> n >> k;
}

void f() {
    for (int i = 0; i < k; i++) {
        int q, a, b;
        cin >> q >> a >> b;
        a++, b++;
        
        if (q == 0) {
            int aa = seg.query(a, a).mn;
            int bb = seg.query(b, b).mn;
            
            seg.modify(a, bb);
            seg.modify(b, aa);
        }
        if (q == 1) {
            mnmx c = seg.query(a, b);
            if (c.mn == a && c.mx == b) cout << "YES\n";
            else cout << "NO\n";
        }
    }
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	int tc; cin >> tc;
	
	while (tc--) {
	    init();
	    
	    input();
	    
	    seg.build(n);
	    
	    f();
	}
	
	return 0;
}
