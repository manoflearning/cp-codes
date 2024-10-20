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

struct Seg {
	int flag;  // array size
	vector<ll> t;

	void build(int N) {
		for (flag = 1; flag < N; flag <<= 1);
		t.resize(2 * flag, INF);
	}
	void modify(int p, ll value) {  // set value at position p
		for (t[p += flag - 1] = value; p > 1; p >>= 1) t[p >> 1] = min(t[p], t[p ^ 1]);
	}
	ll query(int l, int r) {
		return query(l, r, 1, 1, flag);
	}
	ll query(int l, int r, int n, int nl, int nr) {  // sum on interval [l, r]
		if (r < nl || nr < l) return INF;
		if (l <= nl && nr <= r) return t[n];

		int mid = (nl + nr) / 2;
		return min(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}seg;

struct stdidx {
    int std, idx;
};

bool operator<(stdidx& a, stdidx& b) {
    return a.idx < b.idx;
}

int n;
vector<stdidx> a;
vi b[500005];

void input() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a.push_back({ x, i + 1 });
    }
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        b[x].push_back(i + 1);
    }
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        b[x].push_back(i + 1);
    }
}

int f() {
    int ret = n;
    for (auto& i : a) {
        if (seg.query(1, b[i.std][0] - 1) < b[i.std][1]) ret--;
        
        seg.modify(b[i.std][0], b[i.std][1]);
    }
    return ret;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	input();
	
	sort(a.begin(), a.end());
	
	seg.build(n);
	
	cout << f();
	
	return 0;
}
