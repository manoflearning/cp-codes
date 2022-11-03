#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 202020;  // limit for array size

struct Seg {  // 0-indexed
	int n;  // array size
	int t[2 * MAXN];

	void build(int N) {
		n = N;
		//for (int i = 0; i < n; i++) cin >> t[n + i];
		//for (int i = n - 1; i >= 1; i--) t[i] = t[i << 1] + t[i << 1 | 1];
	}
	void modify(int p, int value) {  // set value at position p
		for (t[p += n] += value; p > 1; p >>= 1) t[p >> 1] = max(t[p], t[p ^ 1]);
	}
	int query(int l, int r) {  // sum on interval [l, r)
		int ret = 0;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ret = max(ret, t[l++]);
			if (r & 1) ret = max(ret, t[--r]);
		}
		return ret;
	}
}seg;

int sq;

struct se {
	int s, e, idx;
	bool operator<(const se& rhs) const {
		if (s / sq != rhs.s / sq) return s / sq < rhs.s / sq;
		return e < rhs.e;
	}
};

int n, m, a[101010];
vector<se> q;
vector<int> ans;

void input() {
	// TODO: 1. receive input 2. resize q, ans 3. calculate sq 
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] += 100000;
    }

    q.resize(m);
    ans.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> q[i].s >> q[i].e;
        q[i].idx = i;
    }

    sq = 317;
}

void add(int idx) {
	// TODO: add value at idx from data structure
    seg.modify(a[idx], 1);
}

void del(int idx) {
	// TODO: remove value at idx from data structure
    seg.modify(a[idx], -1);
}

int query() {
	// TODO: extract the current answer of the data structure
    return seg.query(0, 200001);
}

void f() {
	int s = q[0].s, e = q[0].e;
	// TODO: initialize data structure
    for (int i = s; i <= e; i++) add(i);
	ans[q[0].idx] = query();
    
	for (int i = 1; i < q.size(); i++) {
		while (q[i].s < s) add(--s);
		while (e < q[i].e) add(++e);
		while (s < q[i].s) del(s++);
		while (q[i].e < e) del(e--);
		ans[q[i].idx] = query();
	}
}

int main() {
    #ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

	sort(q.begin(), q.end());

    seg.build(200000);

	f();

	for (auto& i : ans) 
		cout << i << '\n';

	return 0;
}