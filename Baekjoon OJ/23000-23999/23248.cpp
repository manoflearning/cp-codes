#include <bits/stdc++.h>
using namespace std;

int flag;
struct Seg {
	vector<int> t;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		t.resize(flag << 1);
	}
	void modify(int p, int val) {
		for (t[p += flag - 1] = val; p > 1; p >>= 1)
			t[p >> 1] = max(t[p], t[p ^ 1]);
	}
	int query(int l, int r, int n = 1, int nl = 1, int nr = flag) {
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];
		int mid = (nl + nr) >> 1;
		return max(query(l, r, n << 1, nl, mid), query(l, r, n << 1 | 1, mid + 1, nr));
	}
}seg;

int m, n, k;
struct Node { int y, x; };
vector<Node> a;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> m >> n >> k;
	a.resize(k);
	for (auto& i : a)
		cin >> i.y >> i.x;

	sort(a.begin(), a.end(), [&](const Node& p1, const Node& p2) {
		return (p1.y ^ p2.y ? p1.y < p2.y : p1.x < p2.x);
	});

	seg.build(n);
	for (auto& i : a) {
		int res = seg.query(i.x + 1, n);
		if (seg.query(i.x, i.x) < res + 1) {
			seg.modify(i.x, res + 1);
		}
	}

	cout << seg.query(1, n);
}