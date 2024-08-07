#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Fenwick { // 0-indexed
	int flag, cnt; // array size
	vector<ll> arr, t;
	void build(int n) {
		for (flag = 1; flag < n; flag <<= 1, cnt++);
		arr.resize(flag);
		t.resize(flag);
	}
	void add(int p, ll value) { // add value at position p
		arr[p] += value;
		while (p < flag) {
			t[p] += value;
			p |= p + 1;
		}
	}
	void modify(int p, ll value) { // set value at position p
		add(p, value - arr[p]);
	};
	ll query(int x) {
		ll ret = 0;
		while (x >= 0) ret += t[x], x = (x & (x + 1)) - 1;
		return ret;
	}
	ll query(int l, int r) {
		return query(r) - (l ? query(l - 1) : 0);
	}
	int kth(int k) { // find the kth smallest number (1-indexed)
		assert(t.back() >= k);
		int l = 0, r = arr.size();
		for (int i = 0; i <= cnt; i++) {
			int mid = (l + r) >> 1;
			ll val = mid ? t[mid - 1] : t.back();
			if (val >= k) r = mid;
			else l = mid, k -= val;
		}
		return l;
	}
}fw;

int main() {
	#ifndef ONLINE_JUDGE
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/input.txt", "r", stdin);
	freopen("/Users/jeongwoo-kyung/Programming/CP-Codes/output.txt", "w", stdout);
	#endif

	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n; cin >> n;
	
	fw.build(2020202);
	for (int i = 0; i < n; i++) {
		int op, x;
		cin >> op >> x;
		
		if (op == 1) fw.add(x, 1);
		if (op == 2) {
			int res = fw.kth(x);
			cout << res << '\n';
			fw.add(res, -1);
		}
	}
}