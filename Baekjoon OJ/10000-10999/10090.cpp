#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Seg {
	int flag;  // array size
	vector<int> t;

	void build(int N) {
		for (flag = 1; flag < N; flag <<= 1);
		t.resize(2 * flag);
	}
	void modify(int p) {  // set value at position p
		for (t[p += flag - 1] = 1; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
	}
	ll query(int l, int r) {
		return query(l, r, 1, 1, flag);
	}
	ll query(int l, int r, int n, int nl, int nr) {  // sum on interval [l, r]
		if (r < nl || nr < l) return 0;
		if (l <= nl && nr <= r) return t[n];

		int mid = (nl + nr) / 2;
		return query(l, r, n << 1, nl, mid) + query(l, r, n << 1 | 1, mid + 1, nr);
	}
}seg;

int n;
vector<int> a;

void input() {
    cin >> n;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
}

ll f() {
    ll ret = 0;
    for (int i = 1; i <= n; i++) {
        ret += seg.query(a[i] + 1, n);
        seg.modify(a[i]);
    }
    return ret;
}

int main() {
	cin.tie(NULL); cout.tie(NULL);
	ios_base::sync_with_stdio(false);

	input();

    seg.build(n);

    cout << f();

	return 0;
}