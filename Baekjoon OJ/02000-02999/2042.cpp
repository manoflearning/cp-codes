#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Fenwick { // 1-indexed
	int flag; // array size
	vector<ll> arr, t;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1);
		arr.resize(flag + 1);
		t.resize(flag + 1);
	}
	void modify(int p, ll value) { // set value at position p
		ll dv = value - arr[p];
		arr[p] = value;
		for (; p <= flag; p += (p & -p)) t[p] += dv;
	}
	ll query(int x) {
		ll ret = 0;
		for (; x; x &= (x - 1)) ret += t[x];
		return ret;
	}
	ll query(int l, int r) {
		return query(r) - query(l - 1);
	}
}fw;

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n, m, k;
	cin >> n >> m >> k;

	fw.build(n);
	for (int i = 1; i <= n; i++) {
		ll value; cin >> value;
		fw.modify(i, value);
	}

	for (int i = 0; i < m + k; i++) {
		ll op, x, y;
		cin >> op >> x >> y;
		if (op == 1) fw.modify(x, y);
		if (op == 2) cout << fw.query(x, y) << '\n';
	}
}